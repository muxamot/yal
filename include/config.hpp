#pragma once

#include <cstdint>

#include "rgba.hpp"

namespace yal
{

constexpr uint32_t WIN_WIDTH = 1280;
constexpr uint32_t WIN_HEIGHT = 720;
constexpr uint32_t CELL_SIZE = 10;
constexpr uint32_t CELLS_X = WIN_WIDTH / CELL_SIZE;
constexpr uint32_t CELLS_Y = WIN_HEIGHT / CELL_SIZE;

static_assert(WIN_WIDTH % CELL_SIZE == 0);
static_assert(WIN_HEIGHT % CELL_SIZE == 0);
static_assert(CELL_SIZE > 3);

#define BG_COLOR COLOR_GRAY
#define FG_COLOR COLOR_ORANGE

}