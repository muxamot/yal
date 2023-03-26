#include <algorithm>

#include "generator.hpp"
#include "log.hpp"

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

Generator::cells_list_t& Generator::getUpdatedList()
{
    return upd_list_;
}

template <uint32_t LIMIT>
static uint32_t limit(int32_t n)
{
    return (n < 0) ? static_cast<uint32_t>(n + LIMIT) : static_cast<uint32_t>(n % LIMIT);
}

void Generator::neighboursOf(uint32_t ux, uint32_t uy, cell_func_t func)
{
    const auto x = static_cast<int32_t>(ux);
    const auto y = static_cast<int32_t>(uy);

    func(limit<CELLS_X>(x - 1), limit<CELLS_Y>(y));
    func(limit<CELLS_X>(x + 1), limit<CELLS_Y>(y));
    func(limit<CELLS_X>(x - 1), limit<CELLS_Y>(y - 1));
    func(limit<CELLS_X>(x), limit<CELLS_Y>(y - 1));
    func(limit<CELLS_X>(x + 1), limit<CELLS_Y>(y - 1));
    func(limit<CELLS_X>(x - 1), limit<CELLS_Y>(y + 1));
    func(limit<CELLS_X>(x), limit<CELLS_Y>(y + 1));
    func(limit<CELLS_X>(x + 1), limit<CELLS_Y>(y + 1));
}

void Generator::cellAndNeighbours(uint32_t x, uint32_t y, cell_func_t func)
{
    func(x, y);
    neighboursOf(x, y, std::move(func));
}

uint32_t Generator::aliveNeighbours(uint32_t x, uint32_t y)
{
    uint32_t result{0};
    neighboursOf(x, y, [&](uint32_t nx, uint32_t ny) {
        if (field_[nx][ny])
            result++;
    });
    return result;
}

bool Generator::willSurvive(uint32_t x, uint32_t y)
{
    const auto alive = aliveNeighbours(x, y);
    return (alive > 1 && alive < 4);
}

bool Generator::willSpawn(uint32_t x, uint32_t y)
{
    return (aliveNeighbours(x, y) == 3);
}

void Generator::makeLookupList()
{
    lookup_list_.clear();
    for (uint32_t x = 0; x < CELLS_X; x++)
        for (uint32_t y = 0; y < CELLS_Y; y++)
            if (field_[x][y])
                cellAndNeighbours(x, y, [&](uint32_t lx, uint32_t ly) {
                    lookup_list_.emplace_back(std::pair{lx, ly});
                });
}

void Generator::generate()
{
    cells_list_t lookup;
    cells_list_t update;

    lookup_list_.sort();
    lookup_list_.unique();

    for (const auto& [x, y] : lookup_list_)
    {
        if (field_[x][y])
        {
            if (!willSurvive(x, y))
            {
                update.emplace_back(std::pair{x, y});
                continue;
            }

            cellAndNeighbours(x, y, [&](uint32_t lx, uint32_t ly) { lookup.emplace_back(std::pair{lx, ly}); });
            continue;
        }

        if (willSpawn(x, y))
        {
            update.emplace_back(std::pair{x, y});
            cellAndNeighbours(x, y, [&](uint32_t lx, uint32_t ly) { lookup.emplace_back(std::pair{lx, ly}); });
        }
    }

    std::swap(lookup, lookup_list_);

    for (const auto& [x, y] : update)
        field_[x][y] = !field_[x][y];

    std::swap(update, upd_list_);
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