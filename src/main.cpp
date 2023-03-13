#include "event_loop.hpp"
#include "log.hpp"
#include "window.hpp"

int main(int argc, char** argv)
{
    using namespace yal;

    events::WindowDrawingEventPublisher draw_publisher;
    events::WindowInputEventPublisher input_publisher;

    auto window = std::make_shared<Window>(WindowDescriptor{1280, 720}, draw_publisher, input_publisher);
    auto evl_controller = std::make_shared<EventLoopController>();

    evl_controller->registerCallback([win = std::move(window)]() -> int { return win->display(); });

    return evl_controller->start();
}