#ifndef TAILS_EXPECTED_HPP
#define TAILS_EXPECTED_HPP

#include <type_traits>

namespace tails
{
    template<typename E>
    class TUnexpected final
    {
    public:
        constexpr TUnexpected() = default;
        constexpr TUnexpected(E&& e)
            : m_unexpected(std::move(e))
        {}

        [[nodiscard]] E& error() & noexcept {return m_unexpected;}
        [[nodiscard]] const E& error() const& noexcept {return m_unexpected;}

    private:
        E m_unexpected;
    };
    
    /**
     * Holds either an expected value, or an unexpected value
     * @tparam T Expected type
     * @tparam E Unexpected value type
     */
    template<typename T, typename E>
    class TExpected final
    {
    public:
        TExpected() = delete;
        constexpr TExpected(T&& value)
            : m_value(std::move(value)), m_hasValue(true)
        {}
        constexpr TExpected(const E& unexpected)
            : m_unexpected(unexpected), m_hasValue(false)
        {}
        constexpr TExpected(const TUnexpected<E>& unexpected)
            : m_unexpected(unexpected.error()), m_hasValue(true)
        {}
        ~TExpected()
        {
            if (m_hasValue)
                m_value.~T();
            else
                m_unexpected.~E();
        }

        explicit operator bool() const noexcept {return m_hasValue;}

        [[nodiscard]] T* operator->() noexcept {return &m_value;}
        [[nodiscard]] T& operator*() noexcept {return m_value;}

        [[nodiscard]] T* getValue() noexcept
        {
            if (m_hasValue)
                return &m_value;

            return nullptr;
        }

        [[nodiscard]] const T* getValue() const noexcept
        {
            if (m_hasValue)
                return &m_value;
            
            return nullptr;
        }

        [[nodiscard]] E getUnexpected() const noexcept {return m_unexpected;}
        
    private:
        union
        {
            T m_value;
            E m_unexpected;
        };
        bool m_hasValue;
    };
}

#endif // TAILS_EXPECTED_HPP
