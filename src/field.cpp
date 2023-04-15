#include "field.hpp"
#include "config.hpp"

namespace yal
{

Field::Field(sptr<Generator> generator)
    : generator_(std::move(generator)){};

void Field::makeStaticBackground() noexcept
{
    for (uint32_t x = 0; x < canvas_->width(); x++)
        for (uint32_t y = 0; y < canvas_->height(); y++)
            canvas_->pixel(x, y) = (x % CELL_SIZE == 0 || y % CELL_SIZE == 0) ? FG_COLOR : BG_COLOR;

    for (uint32_t x = 0; x < canvas_->width(); x++)
        canvas_->pixel(x, canvas_->height() - 1) = FG_COLOR;

    for (uint32_t y = 0; y < canvas_->height(); y++)
        canvas_->pixel(canvas_->width() - 1, y) = FG_COLOR;
}

void Field::fillCell(uint32_t cpx, uint32_t cpy, RGBA color) noexcept
{
    cpx *= CELL_SIZE;
    cpy *= CELL_SIZE;

    for (auto x = cpx + 2; x < (cpx + CELL_SIZE - 1); x++)
        for (auto y = cpy + 2; y < (cpy + CELL_SIZE - 1); y++)
            canvas_->pixel(x, y) = color;
}

void Field::redrawAll() noexcept
{
    if (!canvas_)
        return;

    makeStaticBackground();

    for (uint32_t x = 0; x < CELLS_X; x++)
        for (uint32_t y = 0; y < CELLS_Y; y++)
            fillCell(x, y, generator_->get(x, y) ? FG_COLOR : BG_COLOR);
}

void Field::redraw() noexcept
{
    for (const auto& [x, y] : generator_->getUpdatedList())
        fillCell(x, y, generator_->get(x, y) ? FG_COLOR : BG_COLOR);

    generator_->clearUpdates();
}

void Field::onEvent(const event_t& event) noexcept
{
    // clang-format off
    std::visit(events::overloaded{
        [&](const events::onRedraw& event) { redraw(); },
        [&](const events::onResize& event) { window_ = event.descriptor_; redrawAll();  },
        [&](const events::onCanvasSet& event) { canvas_ = std::move(event.canvas_); redrawAll(); }
    }, event);
    // clang-format on
}

} // namespace yal