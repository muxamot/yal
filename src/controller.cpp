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

    generator_->switchState(x / CELL_SIZE, y / CELL_SIZE);
}

// messy
void Controller::commandInput(SDL_Keycode key)
{
    if (key != SDLK_ESCAPE && key != SDLK_RETURN && key != SDLK_DELETE)
    {
        LOG(INFO) << "No action for this button, try ENTER or ESCAPE";
        return;
    }

    if (key == SDLK_DELETE)
    {
        LOG(INFO) << "Field cleanup" << ((state_ == GameState::GENERATE) ? " game stopped" : "");
        state_ = GameState::FIELD_CONFIGURE;
        generator_->reset();
        return;
    }

    if (key == SDLK_ESCAPE && state_ != GameState::FIELD_CONFIGURE)
    {
        state_ = GameState::FIELD_CONFIGURE;
        LOG(INFO) << "Game stopped, you can configure the field";
        return;
    }

    if (key == SDLK_ESCAPE || state_ == GameState::GENERATE)
        return;

    LOG(INFO) << "Game started";
    state_ = GameState::GENERATE;
    generator_->makeLookupList();
}

void Controller::update() noexcept
{
    if (state_ == GameState::GENERATE) [[likely]]
    {
        if (gen_div_cnt_ == 10)
        {
            generator_->generate();
            gen_div_cnt_ = 0;
        }
        else
        {
            gen_div_cnt_++;
        }
    }
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