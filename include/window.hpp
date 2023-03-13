#pragma once

#include "canvas.hpp"
#include "types.hpp"

#include "events/window_drawing_events.hpp"
#include "events/window_input_events.hpp"

#include <SDL2/SDL.h>

namespace yal
{

class Window
{
private:
    using draw_publisher_t = events::WindowDrawingEventPublisher;
    using input_publisher_t = events::WindowInputEventPublisher;

    draw_publisher_t draw_publisher_;
    input_publisher_t input_publisher_;
    WindowDescriptor desc_;

    SDL_Window* sdl_window_;
    SDL_Cursor* sdl_cursor_;
    SDL_Renderer* renderer_;
    SDL_Texture* screen_texture_{nullptr};

    sptr<Canvas> canvas_;

    void sdlInit();
    bool eventPolling();
    void redraw();
    void createStreamingTexture();

public:
    Window() = delete;
    Window(Window&&) = delete;

    Window(WindowDescriptor, draw_publisher_t, input_publisher_t);
    ~Window();

    int display();
};

} // namespace yal