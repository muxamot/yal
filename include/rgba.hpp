#pragma once

#include <cstddef>

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
#define COLOR_GRAY yal::RGBA{64, 64, 64}
#define COLOR_LIGHT_BLUE yal::RGBA{135, 206, 235}
// clang-format on

} // namespace yal
