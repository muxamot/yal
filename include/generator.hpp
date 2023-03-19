#pragma once

#include <array>
#include <list>

#include "config.hpp"

namespace yal
{

class Generator
{
private:
    using field_state_t = std::array<std::array<bool, CELLS_Y>, CELLS_X>;
    using updated_cells_list_t = std::list<std::pair<uint32_t, uint32_t>>;

    updated_cells_list_t upd_list_;
    field_state_t field_;

public:
    Generator();

    void switchState(uint32_t x, uint32_t y);
    updated_cells_list_t& updatedList();
    bool get(uint32_t x, uint32_t y);
    void generate();
    void clear();
};

} // namespace yal