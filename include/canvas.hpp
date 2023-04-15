#pragma once

#include <cstring>
#include <ranges>
#include <vector>

#include "rgba.hpp"
#include "types.hpp"

namespace yal
{

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