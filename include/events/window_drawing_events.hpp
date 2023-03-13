#pragma once

#include "publisher.hpp"
#include "subscriber.hpp"

#include "canvas.hpp"
#include "types.hpp"

namespace yal::events
{

struct onRedraw
{
};

struct onResize
{
    WindowDescriptor descriptor_;
};

struct onCanvasSet
{
    sptr<Canvas> canvas_;
};

using WindowDrawingEventSubscriber = internal::ISubscriber<onRedraw, onResize, onCanvasSet>;
using WindowDrawingEventPublisher = internal::Publisher<WindowDrawingEventSubscriber>;

} // namespace yal::events