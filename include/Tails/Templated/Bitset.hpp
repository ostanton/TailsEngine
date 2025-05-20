#ifndef TAILS_BITSET_HPP
#define TAILS_BITSET_HPP

#include <Tails/Concepts.hpp>

#include <initializer_list>

namespace tails
{
    /**
     * Basic bitset wrapper. Assumes enumerator value are bits (like 1 << 0, 1 << 1, etc.)
     * @tparam EnumType Enumeration type
     * @tparam FlagSize Size of the enumeration/bit set (defaults to underlying value of EnumType)
     */
    template<Enum EnumType, Integral FlagSize = std::underlying_type_t<EnumType>>
    class TBitset final
    {
    public:
        using UnderlyingType = std::underlying_type_t<EnumType>;
        
        constexpr TBitset() noexcept = default;
        constexpr TBitset(FlagSize flags) noexcept
            : m_flags(flags)
        {}
        constexpr TBitset(std::initializer_list<EnumType> bits) noexcept
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

        [[nodiscard]] constexpr bool anyBitSet() const noexcept {return m_flags != 0;}
        
    private:
        FlagSize m_flags {0};
    };
}

#endif // TAILS_BITSET_HPP
