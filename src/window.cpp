#include <exception>

#include "log.hpp"
#include "window.hpp"

namespace yal
{

Window::Window(WindowDescriptor desc, draw_publisher_t draw_publisher, input_publisher_t input_publisher)
    : draw_publisher_(std::move(draw_publisher))
    , input_publisher_(std::move(input_publisher))
    , desc_(desc)
    , canvas_(std::make_shared<Canvas>(desc_))
{
    sdlInit();
    draw_publisher_.publish(events::onCanvasSet{canvas_});
}

Window::~Window()
{
    SDL_DestroyTexture(screen_texture_);
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(sdl_window_);
    SDL_FreeCursor(sdl_cursor_);
}

void Window::sdlInit()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        LOG(ERROR) << "Unable to init SDL, error: " << SDL_GetError();
        throw std::logic_error{"SDL initialization failed"};
    }

    sdl_window_ = SDL_CreateWindow("Yet another Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   desc_.width_, desc_.height_, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!sdl_window_)
    {
        LOG(ERROR) << "Failed to create SDL window, SDL says: " << SDL_GetError();
        throw std::logic_error("Window initialization failed");
    }

    // Create a renderer with vsync enabled.
    renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_PRESENTVSYNC);

    // Create a streaming texture
    createStreamingTexture();

    if (!renderer_ || !screen_texture_)
    {
        LOG(ERROR) << "Failed to create renderer instance, SDL says: " << SDL_GetError();
        throw std::logic_error("Window initialization failed");
    }

    LOG(INFO) << "Window initialized";
    draw_publisher_.publish(events::onResize{desc_});
}

void Window::createStreamingTexture()
{
    if (screen_texture_)
        SDL_DestroyTexture(screen_texture_);

    screen_texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, desc_.width_,
                                        desc_.height_);

    if (!screen_texture_)
    {
        LOG(ERROR) << "Failed to create straming texture, SDL says: " << SDL_GetError();
        throw std::logic_error("Texture allocation failed");
    }
}

bool Window::eventPolling()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return false;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                desc_.width_ = event.window.data1;
                desc_.height_ = event.window.data2;
                canvas_->resize(desc_);
                createStreamingTexture();

                draw_publisher_.publish(events::onResize{desc_});
            }
            break;
        // keypress processing
        case SDL_KEYDOWN:
            input_publisher_.publish(events::onKeyDown{event.key.keysym.sym});
            break;
        case SDL_KEYUP:
            input_publisher_.publish(events::onKeyUp{event.key.keysym.sym});
            break;
        case SDL_MOUSEBUTTONDOWN:
            input_publisher_.publish(events::onMouseDown{event.button.x, event.button.y});
        }
    }

    return true;
}

void Window::redraw()
{
    draw_publisher_.publish(events::onRedraw{});
}

int Window::display()
{
    if (!eventPolling())
        return 1;

    redraw();

    SDL_UpdateTexture(screen_texture_, NULL, canvas_->data(), canvas_->stride());
    SDL_RenderCopy(renderer_, screen_texture_, NULL, NULL);
    SDL_RenderPresent(renderer_);

    return 0;
}

} // namespace yal