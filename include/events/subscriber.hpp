#pragma once

#include <variant>

namespace yal::events
{

namespace internal
{

template <typename... Events>
class ISubscriber
{
public:
    using event_t = std::variant<Events...>;

    virtual void onEvent(const event_t&) noexcept = 0;
};

} // namespace internal

// overloaded helper and its deduction guide
template <class... Ts>
struct overloaded : Ts...
{
    using Ts::operator()...;
};

template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

} // namespace yal::events