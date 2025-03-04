#ifndef TAILS_UNIQUE_PTR_HPP
#define TAILS_UNIQUE_PTR_HPP

#include <memory>

namespace tails
{
    template<typename T, typename DeleteT = std::default_delete<T>>
    using TUniquePtr = std::unique_ptr<T, DeleteT>;

    // TODO - possible TUniqueRef for forced unique allocation

    template<typename T, typename... ArgsT>
    [[nodiscard]] TUniquePtr<T> makeUnique(ArgsT&&... args)
    {
        return std::make_unique<T>(std::forward<ArgsT>(args)...);
    }
}

#endif // TAILS_UNIQUE_PTR_HPP
