#pragma once

#include "generator.hpp"
#include "types.hpp"

#include "events/window_input_events.hpp"

namespace yal
{

class Controller : events::WindowInputEventSubscriber
{
private:
    enum class GameState
    {
        FIELD_CONFIGURE,
        GENERATE
    };

    GameState state_;
    sptr<Generator> generator_;

    void handleCellInput(uint32_t x, uint32_t y);

public:
    Controller(sptr<Generator>);

    void onEvent(const event_t& event) noexcept;
};

} // namespace yal