#pragma once

#include <cstring>
#include <ranges>
#include <vector>

#include "types.hpp"

namespace yal
{

using cbyte_t = unsigned char;

struct RGBA
{
    RGBA() = default;
    explicit RGBA(cbyte_t r, cbyte_t g, cbyte_t b, cbyte_t a = 255U)
        : a_(static_cast<std::byte>(a))
        , b_(static_cast<std::byte>(b))
        , g_(static_cast<std::byte>(g))
        , r_(static_cast<std::byte>(r)){};

    // Little endian sequence
    std::byte a_{255};
    std::byte b_{0};
    std::byte g_{0};
    std::byte r_{0};
};

using Pixel = RGBA;

static_assert(sizeof(Pixel) == 4, "Invalid pixel size");

// clang-format off
#define COLOR_WHITE yal::RGBA{255, 255, 255}
#define COLOR_BLACK yal::RGBA{0, 0, 0}
#define COLOR_RED yal::RGBA{255, 0, 0}
#define COLOR_ORANGE yal::RGBA{255, 140, 0}
#define COLOR_YELLOW yal::RGBA{255, 255, 0}
#define COLOR_GREEN yal::RGBA{0, 255, 0}
#define COLOR_BLUE yal::RGBA{0, 0, 255}
#define COLOR_PURPLE yal::RGBA{100, 0, 100}
#define COLOR_GRAY yal::RGBA{50, 50, 50}
#define COLOR_LIGHT_BLUE yal::RGBA{135, 206, 235}
// clang-format on

class Canvas
{
private:
    uint32_t width_;
    uint32_t height_;
    uint32_t length_;
    std::vector<Pixel> canvas_buffer_;

public:
    Canvas(const WindowDescriptor& desc)
        : width_(desc.width_)
        , height_(desc.height_)
        , length_(width_ * height_)
    {
        canvas_buffer_.resize(length_);
    }

    ~Canvas() = default;

    void resize(const WindowDescriptor& desc)
    {
        width_ = desc.width_;
        height_ = desc.height_;
        length_ = std::max(width_ * height_, length_);
        canvas_buffer_.resize(length_);
    }

    Pixel& pixel(uint32_t x, uint32_t y)
    {
        return canvas_buffer_[x + y * width_];
    }

    void set(const std::ranges::range auto& range, const Pixel& px)
    {
        std::ranges::fill(range, px);
    }

    auto horizontalRange(std::size_t size, std::size_t offset = 0)
    {
        auto begin = canvas_buffer_.begin() + (offset * width_);
        return std::ranges::subrange{begin, begin + (size * width_)};
    }

    auto horizontalRange()
    {
        return std::ranges::subrange{canvas_buffer_};
    }

    void clear()
    {
        set(horizontalRange(), COLOR_BLACK);
    }

    const unsigned* data() noexcept
    {
        return reinterpret_cast<const unsigned*>(canvas_buffer_.data());
    }

    uint32_t width() const noexcept
    {
        return width_;
    };

    uint32_t height() const noexcept
    {
        return height_;
    };

    uint32_t stride() const noexcept
    {
        return width_ * sizeof(Pixel);
    };
};

} // namespace yal