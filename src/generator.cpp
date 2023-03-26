#include <algorithm>
#include <ranges>

#include "generator.hpp"

namespace yal
{

Generator::Generator()
{
    blankField(UpdateMode::SILENT);
}

void Generator::switchState(uint32_t x, uint32_t y)
{
    if (x > CELLS_X || y > CELLS_Y)
        throw std::runtime_error{"Unrecoverable runtime error - index was out of range"};

    field_[x][y] = !field_[x][y];
    upd_list_.emplace_back(std::pair{x, y});
}

bool Generator::get(uint32_t x, uint32_t y)
{
    if (x > CELLS_X || y > CELLS_Y)
        throw std::runtime_error{"Unrecoverable runtime error - index was out of range"};

    return field_[x][y];
}

Generator::updated_cells_list_t& Generator::getUpdatedList()
{
    return upd_list_;
}

void Generator::generate()
{
}

void Generator::clearUpdates()
{
    upd_list_.clear();
}

void Generator::blankField(UpdateMode mode)
{
    for (uint32_t x = 0; x < CELLS_X; x++)
        for (uint32_t y = 0; y < CELLS_Y; y++)
        {
            field_[x][y] = false;
            if (mode == UpdateMode::PUBLIC)
                upd_list_.emplace_back(std::pair{x, y});
        }
}

void Generator::reset()
{
    clearUpdates();
    blankField(UpdateMode::PUBLIC);
}

} // namespace yal