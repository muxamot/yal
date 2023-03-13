#include "controller.hpp"

namespace yal
{

Controller::Controller(sptr<Generator> generator)
    : generator_(std::move(generator)){};

void Controller::handleCellInput(uint32_t x, uint32_t y)
{
    generator_->switchState(x / CELL_SIZE, y / CELL_SIZE);
}

void Controller::onEvent(const event_t& event) noexcept
{
    // clang-format off
    std::visit(events::overloaded{
        [&](const events::onMouseDown& event) { handleCellInput(event.x_, event.y_); },
        [&](auto& event) { /* placeholder */ }
    }, event);
    // clang-format on
}

} // namespace yal