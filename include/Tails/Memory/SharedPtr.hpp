#ifndef TAILS_SHARED_PTR_HPP
#define TAILS_SHARED_PTR_HPP

#include <memory>

namespace tails
{
    template<typename T>
    using TSharedPtr = std::shared_ptr<T>;

    // TODO - implement as ref instead of ptr
    template<typename T>
    using TSharedRef = std::shared_ptr<T>;

    template<typename T>
    using TWeakPtr = std::weak_ptr<T>;

    template<typename T, typename... ArgsT>
    [[nodiscard]] TSharedRef<T> makeShared(ArgsT&&... args)
    {
        return std::make_shared<T>(std::forward<ArgsT>(args)...);
    }
}

#endif // TAILS_SHARED_PTR_HPP
