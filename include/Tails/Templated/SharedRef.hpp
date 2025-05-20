#ifndef TAILS_SHARED_REF_HPP
#define TAILS_SHARED_REF_HPP

#include <Tails/Core.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/Assert.hpp>

#include <memory>

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
        TSharedRef(std::shared_ptr<T> ptr)
        {
            TAILS_ASSERT(ptr != nullptr, "Creating a shared ref from null shared ptr is not allowed!");
            m_ptr = std::move(ptr);
        }
        TSharedRef(const TSharedRef&) = default;
        TSharedRef(TSharedRef&&) = default;
        TSharedRef& operator=(const TSharedRef&) = default;
        TSharedRef& operator=(TSharedRef&&) = default;
        ~TSharedRef() = default;

        TSharedRef& operator=(std::nullptr_t) = delete;
        TSharedRef& operator=(std::shared_ptr<T> ptr)
        {
            TAILS_ASSERT(ptr != nullptr, "Creating a shared ref from null shared_ptr is not allowed!");
            m_ptr = std::move(ptr);
            return *this;
        }

        explicit operator std::shared_ptr<T>() const {return m_ptr;}
        [[nodiscard]] T* operator->() const noexcept {return m_ptr.get();}
        [[nodiscard]] T& operator*() const noexcept {return *m_ptr;}

    private:
        std::shared_ptr<T> m_ptr;
    };

    template<typename T, typename... ArgsT>
    requires ConstructibleFrom<T, ArgsT...>
    TSharedRef<T> makeShared(ArgsT&&... args)
    {
        return std::make_shared<T>(std::forward<ArgsT>(args)...);
    }
}

#endif // TAILS_SHARED_REF_HPP
