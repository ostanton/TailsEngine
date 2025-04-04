#ifndef TAILS_BITSET_HPP
#define TAILS_BITSET_HPP

#include <type_traits>
#include <initializer_list>

namespace tails
{
    template<typename EnumType, typename FlagSize = std::underlying_type_t<EnumType>>
    class TBitset final
    {
        static_assert(std::is_enum_v<EnumType>, "Cannot use TBitset with a non-enum type");
        static_assert(std::is_integral_v<FlagSize>, "Cannot use TBitset with a non-integer flag size");
        
    public:
        using UnderlyingType = std::underlying_type_t<EnumType>;
        
        constexpr TBitset() noexcept = default;
        constexpr explicit TBitset(FlagSize flags) noexcept
            : m_flags(flags)
        {}
        constexpr explicit TBitset(std::initializer_list<EnumType> bits) noexcept
        {
            for (const auto bit : bits)
            {
                m_flags |= static_cast<UnderlyingType>(bit);
            }
        }
        constexpr TBitset(const TBitset&) noexcept = default;
        constexpr TBitset(TBitset&&) noexcept = default;
        constexpr TBitset& operator=(const TBitset&) noexcept = default;
        constexpr TBitset& operator=(TBitset&&) noexcept = default;
        ~TBitset() noexcept = default;

        [[nodiscard]] constexpr bool operator==(const TBitset& other) const noexcept {return m_flags == other.m_flags;}
        [[nodiscard]] constexpr bool operator!=(const TBitset& other) const noexcept {return !(*this == other);}

        constexpr void setBit(const EnumType bit) noexcept
        {
            m_flags |= static_cast<UnderlyingType>(bit);
        }

        constexpr void flipBit(const EnumType bit) noexcept
        {
            m_flags &= ~static_cast<UnderlyingType>(bit);
        }

        constexpr void clearBit(const EnumType bit) noexcept
        {
            m_flags ^= static_cast<UnderlyingType>(bit);
        }

        constexpr void reset() noexcept {m_flags = 0;}

        [[nodiscard]] constexpr bool isBitSet(const EnumType bit) const noexcept
        {
            return (m_flags & static_cast<UnderlyingType>(bit)) == static_cast<UnderlyingType>(bit);
        }
        
    private:
        FlagSize m_flags {0};
    };
}

#endif // TAILS_BITSET_HPP
