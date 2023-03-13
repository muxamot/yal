#include "boost/range/algorithm.hpp"

#include "event_loop.hpp"
#include "log.hpp"

#include "emscripten.h"

namespace yal
{

EventLoopController* wasm_el_registrator;

void wasm_C_call_wrapper()
{
    wasm_el_registrator->doRunLoop();
}

void EventLoopController::registerCallback(el_cb_t cb)
{
    cbs_.emplace_back(std::move(cb));
}

void EventLoopController::doRunLoop()
{
    boost::range::for_each(cbs_, [&](auto cb) {
        if (cb() != 0)
            LOG(ERROR) << "something wrong";
    });
}

int EventLoopController::start()
{
    wasm_el_registrator = this;
    emscripten_set_main_loop(wasm_C_call_wrapper, 0, 1);
    return 0;
}

} // namespace yal