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
    using cells_list_t = std::list<std::pair<uint32_t, uint32_t>>;
    using cell_func_t = std::function<void(uint32_t, uint32_t)>;

    enum UpdateMode
    {
        PUBLIC,
        SILENT
    };

    cells_list_t lookup_list_;
    cells_list_t upd_list_;
    field_state_t field_;

    void blankField(UpdateMode);
    void neighboursOf(uint32_t, uint32_t, cell_func_t);
    void cellAndNeighbours(uint32_t, uint32_t, cell_func_t);
    uint32_t aliveNeighbours(uint32_t, uint32_t);
    bool willSurvive(uint32_t, uint32_t);
    bool willSpawn(uint32_t, uint32_t);

public:
    Generator();

    void switchState(uint32_t, uint32_t);
    cells_list_t& getUpdatedList();
    bool get(uint32_t, uint32_t);

    void makeLookupList();
    void generate();

    void clearUpdates();
    void reset();
};

} // namespace yal