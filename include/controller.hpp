#pragma once

#include "generator.hpp"
#include "types.hpp"

#include "events/window_drawing_events.hpp"
#include "events/window_input_events.hpp"

namespace yal
{

class Controller : public events::WindowInputEventSubscriber, public events::WindowDrawingEventSubscriber
{
private:
    enum class GameState
    {
        FIELD_CONFIGURE,
        GENERATE
    };

    uint32_t gen_div_cnt_;
    GameState state_;
    sptr<Generator> generator_;

    void handleCellInput(uint32_t, uint32_t);
    void commandInput(SDL_Keycode);
    void update() noexcept;

public:
    Controller(sptr<Generator>);

    void onEvent(const events::WindowInputEventSubscriber::event_t& event) noexcept;
    void onEvent(const events::WindowDrawingEventSubscriber::event_t& event) noexcept;
};

} // namespace yal