#pragma once

#include <functional>

namespace yal
{

class EventLoopController
{
private:
    using el_cb_t = std::function<int()>;

    std::vector<el_cb_t> cbs_;

    friend void wasm_C_call_wrapper();
    void doRunLoop();

public:
    void registerCallback(el_cb_t);
    int start();
};

}