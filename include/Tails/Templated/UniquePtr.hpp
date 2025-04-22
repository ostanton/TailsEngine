#ifndef TAILS_UNIQUE_PTR_HPP
#define TAILS_UNIQUE_PTR_HPP

#include <Tails/Core.hpp>
#include <Tails/Memory.hpp>

#include <memory>

namespace tails
{
    template<typename T>
    struct TAILS_API TUniqueDeleter final
    {
        constexpr void operator()(T* ptr) const noexcept
        {
            static_assert(0 < sizeof(T), "Cannot delete and incomplete type");
            mem::destroy(ptr);
        }
    };
    
    template<typename T>
    using TUniquePtr = std::unique_ptr<T, TUniqueDeleter<T>>;

    template<typename T, typename... ArgsT>
    [[nodiscard]] constexpr TUniquePtr<T> makeUnique(ArgsT&&... args)
    {
        return TUniquePtr<T>(mem::newObject<T>(std::forward<ArgsT>(args)...));
    }
}

#endif // TAILS_UNIQUE_PTR_HPP
