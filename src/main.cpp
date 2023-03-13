#include "config.hpp"
#include "event_loop.hpp"
#include "field.hpp"
#include "log.hpp"
#include "window.hpp"

int main(int argc, char** argv)
{
    using namespace yal;

    events::WindowDrawingEventPublisher draw_publisher;
    events::WindowInputEventPublisher input_publisher;

    auto field = std::make_shared<Field>();
    draw_publisher.registerSubsciber(field);

    auto window = std::make_shared<Window>(WindowDescriptor{WIN_WIDTH, WIN_HEIGHT}, draw_publisher, input_publisher);
    auto evl_controller = std::make_shared<EventLoopController>();

    evl_controller->registerCallback([win = std::move(window)]() -> int { return win->display(); });

    return evl_controller->start();
}