#include "controller.hpp"
#include "log.hpp"

namespace yal
{

Controller::Controller(sptr<Generator> generator)
    : generator_(std::move(generator)){};

void Controller::handleCellInput(uint32_t x, uint32_t y)
{
    if (state_ != GameState::FIELD_CONFIGURE)
        return;

    LOG(INFO) << "x: " << x << ", y: " << y;
    generator_->switchState(x / CELL_SIZE, y / CELL_SIZE);
}

void Controller::commandInput(SDL_Keycode key)
{
    if (key != SDLK_ESCAPE && key != SDLK_RETURN)
    {
        LOG(INFO) << "No action for this button, try ENTER or ESCAPE";
        return;
    }

    if (key == SDLK_ESCAPE && state_ != GameState::FIELD_CONFIGURE)
    {
        state_ = GameState::FIELD_CONFIGURE;
        LOG(INFO) << "Game stopped, you can configure the field";
        return;
    }

    if (state_ == GameState::GENERATE)
        return;

    state_ = GameState::GENERATE;
    LOG(INFO) << "Game started";
}

void Controller::update() noexcept
{
    if (state_ == GameState::GENERATE) [[likely]]
        generator_->generate();
}

void Controller::onEvent(const events::WindowInputEventSubscriber::event_t& event) noexcept
{
    // clang-format off
    std::visit(events::overloaded{
        [&](const events::onMouseDown& event) { handleCellInput(event.x_, event.y_); },
        [&](const events::onKeyUp & event)    { commandInput(event.key_); },
        [&](auto& event)                      { /* placeholder */ }
    }, event);
    // clang-format on
}

void Controller::onEvent(const events::WindowDrawingEventSubscriber::event_t& event) noexcept
{
    // clang-format off
    std::visit(events::overloaded{
        [&](const events::onRedraw& event) { update(); },
        [&](auto& event)                   { /* placeholder */ }
    }, event);
    // clang-format on
}

} // namespace yal