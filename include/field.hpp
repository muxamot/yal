#pragma once

#include <variant>

#include "events/window_drawing_events.hpp"
#include "generator.hpp"

namespace yal
{

class Field : public events::WindowDrawingEventSubscriber
{
private:
    WindowDescriptor window_;
    sptr<Canvas> canvas_;
    sptr<Generator> generator_;

    void makeStaticBackground() noexcept;
    void fillCell(uint32_t, uint32_t, RGBA) noexcept;
    void redrawAll() noexcept;
    void redraw() noexcept;

public:
    Field(sptr<Generator>);

    void onEvent(const event_t& event) noexcept;
};

}; // namespace yal