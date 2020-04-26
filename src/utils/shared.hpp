#pragma once

#include <memory>

namespace engine
{

    template <class T>
    using AikoPtr = std::shared_ptr<T>;

    template <class T>
    using AikoUPtr = std::unique_ptr<T>;

}
