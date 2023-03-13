#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace yal
{

template <typename T>
using sptr = std::shared_ptr<T>;

template <typename T>
using uptr = std::unique_ptr<T>;

template <typename T>
using wptr = std::weak_ptr<T>;

struct WindowDescriptor
{
    int width_;
    int height_;
};

} // namespace yal