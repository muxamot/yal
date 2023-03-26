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

    enum UpdateMode
    {
        PUBLIC,
        SILENT
    };

    updated_cells_list_t upd_list_;
    field_state_t field_;

    void blankField(UpdateMode);

public:
    Generator();

    void switchState(uint32_t, uint32_t);
    updated_cells_list_t& getUpdatedList();
    bool get(uint32_t x, uint32_t y);
    void generate();
    void clearUpdates();
    void reset();
};

} // namespace yal