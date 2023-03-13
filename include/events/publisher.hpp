#pragma once

#include <algorithm>
#include <list>

#include "types.hpp"

namespace yal::events::internal
{

template <typename T>
class Publisher
{
private:
    std::list<sptr<T>> subscribers_;

public:
    void registerSubsciber(sptr<T> subscriber)
    {
        subscribers_.emplace_back(std::move(subscriber));
    }

    void unregisterSubscriber(sptr<T> subscriber)
    {
        std::erase(subscribers_, subscriber);
    }

    void publish(const T::event_t& event) noexcept
    {
        std::ranges::for_each(subscribers_, [&](const auto& sub) { sub->onEvent(event); });
    }
};

} // namespace yal::events::internal