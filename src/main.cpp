#include "event_loop.hpp"
#include "log.hpp"

int main(int argc, char** argv)
{
    auto evl_controller = std::make_shared<yal::EventLoopController>();
    evl_controller->registerCallback([&]() -> int {
        LOG(INFO) << "fuck!";
        return 0;
    });

    return evl_controller->start();
}