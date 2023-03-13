#pragma once

#include "publisher.hpp"
#include "subscriber.hpp"

#include <SDL2/SDL_keycode.h>

namespace yal::events
{

struct onKeyDown
{
    SDL_Keycode key_;
};

struct onKeyUp
{
    SDL_Keycode key_;
};

struct onMouseDown
{
    int x_;
    int y_;
};

using WindowInputEventSubscriber = internal::ISubscriber<onKeyDown, onKeyUp, onMouseDown>;
using WindowInputEventPublisher = internal::Publisher<WindowInputEventSubscriber>;

} // namespace yal::events