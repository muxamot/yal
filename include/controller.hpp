#pragma once

#include "generator.hpp"
#include "types.hpp"

#include "events/window_input_events.hpp"

namespace yal
{

class Controller : public events::WindowInputEventSubscriber
{
private:
    enum class GameState
    {
        FIELD_CONFIGURE,
        GENERATE
    };

    GameState state_;
    sptr<Generator> generator_;

    void handleCellInput(uint32_t, uint32_t);

public:
    Controller(sptr<Generator>);

    void onEvent(const event_t& event) noexcept;
};

} // namespace yal