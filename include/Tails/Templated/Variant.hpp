#ifndef TAILS_VARIANT_HPP
#define TAILS_VARIANT_HPP

#include <variant>

namespace tails
{
    namespace impl
    {
        template<typename... ArgsT>
        using TVariantImpl = std::variant<ArgsT...>;
    }

    template<typename... ArgsT>
    class TVariant final
    {
    public:
        TVariant() = default;
        template<typename T>
        constexpr TVariant(T&& obj)
            : m_variant(std::forward<T>(obj))
        {}
        constexpr explicit TVariant(ArgsT&&... args)
            : m_variant(std::forward<ArgsT>(args)...)
        {}

        template<typename T>
        [[nodiscard]] constexpr bool holdsAlternative() const noexcept
        {
            return std::holds_alternative<T>(m_variant);
        }

        template<typename T> T* get() {return std::get_if<T>(&m_variant);}
        template<typename T> const T* get() const {return std::get_if<T>(&m_variant);}

        [[nodiscard]] bool operator==(const TVariant& other) const noexcept {return m_variant == other.m_variant;}
        [[nodiscard]] bool operator!=(const TVariant& other) const noexcept {return !(*this == other);}
        
    private:
        impl::TVariantImpl<ArgsT...> m_variant;
    };
}

#endif // TAILS_VARIANT_HPP
