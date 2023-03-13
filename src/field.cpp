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
            canvas_->pixel(x, y) = (x % CELL_SIZE == 0 || y % CELL_SIZE == 0) ? COLOR_BLACK : COLOR_WHITE;

    for (uint32_t x = 0; x < canvas_->width(); x++)
        canvas_->pixel(x, canvas_->height() - 1) = COLOR_BLACK;

    for (uint32_t y = 0; y < canvas_->height(); y++)
        canvas_->pixel(canvas_->width() - 1, y) = COLOR_BLACK;
}

void Field::onEvent(const event_t& event) noexcept
{
    // clang-format off
    std::visit(events::overloaded{
        [&](const events::onRedraw& event) { makeStaticBackground(); },
        [&](const events::onResize& event) { window_ = event.descriptor_; },
        [&](const events::onCanvasSet& event) { canvas_ = std::move(event.canvas_); }
    }, event);
    // clang-format on
}

} // namespace yal