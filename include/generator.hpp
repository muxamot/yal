#pragma once

#include <array>

#include "config.hpp"

namespace yal
{

class Generator
{
private:
    using field_state_t = std::array<std::array<bool, CELLS_Y>, CELLS_X>;

    field_state_t field_;

public:
    Generator();

    void switchState(uint32_t x, uint32_t y);
    bool get(uint32_t x, uint32_t y);
    void generate();
};

} // namespace yal