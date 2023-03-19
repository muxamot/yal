#include <algorithm>
#include <ranges>

#include "generator.hpp"

namespace yal
{

Generator::Generator()
{
    for (auto& line : field_)
        std::ranges::fill(line, false);
}

void Generator::switchState(uint32_t x, uint32_t y)
{
    if (x > CELLS_X || y > CELLS_Y)
        throw std::runtime_error{"Unrecoverable runtime error - index was out of range"};

    field_[x][y] = !field_[x][y];
}

bool Generator::get(uint32_t x, uint32_t y)
{
    if (x > CELLS_X || y > CELLS_Y)
        throw std::runtime_error{"Unrecoverable runtime error - index was out of range"};

    return field_[x][y];
}

Generator::updated_cells_list_t& Generator::updatedList()
{
    return upd_list_;
}

void Generator::generate()
{
}

void Generator::clear()
{
    upd_list_.clear();
}

} // namespace yal