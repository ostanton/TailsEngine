#ifndef TAILS_OPTIONAL_HPP
#define TAILS_OPTIONAL_HPP

#include <optional>

namespace tails
{
    namespace impl
    {
        template<typename T>
        using TOptionalImpl = std::optional<T>;
    }

    struct SNullOpt
    {
        struct STag {};
        constexpr explicit SNullOpt(STag) {}
    };

    inline constexpr SNullOpt nullOpt {SNullOpt::STag{}};

    /**
     * Optionally contains a value
     * @tparam T Value type
     */
    template<typename T>
    class TOptional final
    {
    public:
        constexpr TOptional() noexcept = default;
        constexpr TOptional(SNullOpt) noexcept {}
        TOptional(const TOptional&) = default;
        TOptional(TOptional&&) noexcept = default;
        template<typename U>
        explicit TOptional(const TOptional<U>& other) noexcept(std::is_nothrow_constructible_v<T, const U&>)
            : m_optional(other.m_optional)
        {}
        template<typename U>
        explicit TOptional(TOptional<U>&& other) noexcept(std::is_nothrow_constructible_v<T, U>)
            : m_optional(std::move(other.m_optional))
        {}
        template<typename U>
        TOptional(U&& val) noexcept(std::is_nothrow_constructible_v<T, U>)
            : m_optional(std::forward<U>(val))
        {}
        TOptional& operator=(const TOptional&) = default;
        TOptional& operator=(TOptional&&) noexcept = default;
        ~TOptional() = default;

        template<typename... ArgsT>
        constexpr T& emplace(ArgsT&&... args) noexcept(std::is_nothrow_constructible_v<T>)
        {
            return m_optional.emplace(std::forward<ArgsT>(args)...);
        }

        constexpr void reset() noexcept
        {
            m_optional.reset();
        }

        [[nodiscard]] T& get() & {return m_optional.value();}
        [[nodiscard]] const T& get() const & {return m_optional.value();}
        [[nodiscard]] T& get() && {return m_optional.value();}
        [[nodiscard]] const T& get() const && {return m_optional.value();}

        [[nodiscard]] constexpr bool isValid() const noexcept {return m_optional.has_value();}

        constexpr T& operator*() & noexcept {return *m_optional;}
        constexpr const T& operator*() const & noexcept {return *m_optional;}
        constexpr T&& operator*() && noexcept {return *m_optional;}
        constexpr const T&& operator*() const && noexcept {return *m_optional;}

        [[nodiscard]] constexpr T* operator->() noexcept {return m_optional.operator->();}
        [[nodiscard]] constexpr const T* operator->() const noexcept {return m_optional.operator->();}

        explicit operator bool() const noexcept {return m_optional.has_value();}
        
    private:
        impl::TOptionalImpl<T> m_optional;
    };

    template<typename T, typename... ArgsT>
    [[nodiscard]] constexpr TOptional<T> makeOptional(ArgsT&&... args)
    {
        return TOptional<T> {std::forward<ArgsT>(args)...};
    }

    /**
     * Reference wrapper
     * @tparam T Type
     */
    template<typename T>
    class TReference final
    {
    public:
        TReference() = delete;
        constexpr TReference(T& val)
            : m_ptr(&val)
        {}

        constexpr operator T&() const noexcept {return *m_ptr;}
        [[nodiscard]] constexpr T& get() const noexcept {return *m_ptr;}
        
    private:
        T* m_ptr {nullptr};
    };

    /**
     * Optional reference
     * @param T type
     */
    template<typename T>
    using TOptRef = TOptional<TReference<T>>;
}

#endif // TAILS_OPTIONAL_HPP
