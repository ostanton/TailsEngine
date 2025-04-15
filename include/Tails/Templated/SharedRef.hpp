#ifndef TAILS_SHARED_REF_HPP
#define TAILS_SHARED_REF_HPP

#include <Tails/Core.hpp>

#include <memory>
#include <iostream>

namespace tails
{
    /**
     * Same as std::shared_ptr, except cannot be null
     * @tparam T Type
     */
    template<typename T>
    class TSharedRef final
    {
    public:
        TSharedRef() = delete;
        TSharedRef(std::nullptr_t) = delete;
        TSharedRef(const std::shared_ptr<T>& ptr)
        {
            TAILS_ASSERT(ptr != nullptr, "Creating a shared ref from null shared ptr is not allowed!");
            m_ptr = ptr;
        }
        TSharedRef(const TSharedRef&) = default;
        TSharedRef(TSharedRef&&) = default;
        TSharedRef& operator=(const TSharedRef&) = default;
        TSharedRef& operator=(TSharedRef&&) = default;
        ~TSharedRef() = default;

        [[nodiscard]] std::shared_ptr<T> toSharedPtr() const noexcept {return m_ptr;}
        
    private:
        std::shared_ptr<T> m_ptr;
    };

    template<typename T, typename... ArgsT>
    TSharedRef<T> makeSharedRef(ArgsT&&... args)
    {
        return std::make_shared<T>(std::forward<ArgsT>(args)...);
    }
}

#endif // TAILS_SHARED_REF_HPP
