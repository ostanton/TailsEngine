#ifndef TAILS_HANDLE_HPP
#define TAILS_HANDLE_HPP

#include <Tails/Config.hpp>
#include <Tails/Maths.hpp>

#include <optional>

namespace tails
{
    /**
     * Optional size_t wrapper for comparing hashable values
     */
    struct TAILS_API SHandle final
    {
        SHandle()
            : m_value(std::nullopt) {}
        SHandle(const SHandle&) = default;
        SHandle(SHandle&&) = default;
        SHandle& operator=(const SHandle&) = default;
        SHandle& operator=(SHandle&&) = default;
        ~SHandle() = default;

        template<Hashable T>
        explicit SHandle(T in) : m_value(hash(in)) {}
        explicit SHandle(std::size_t in) : m_value(in) {}

        template<Hashable T>
        SHandle& operator=(T in) {m_value = hash(in); return *this;}
        SHandle& operator=(std::size_t in) {m_value = in; return *this;}
        
        [[nodiscard]] bool isValid() const noexcept {return m_value.has_value();}

        [[nodiscard]] explicit operator bool() const
        {
            return isValid();
        }

        [[nodiscard]] std::size_t operator*() const
        {
            return *m_value;
        }

        [[nodiscard]] bool operator==(const SHandle&) const = default;
        [[nodiscard]] bool operator!=(const SHandle&) const = default;

        template<Hashable T>
        [[nodiscard]] bool operator==(T in) const {return isValid() ? hash(in) == m_value.value() : false;}
        template<Hashable T>
        [[nodiscard]] bool operator!=(T in) const {return isValid() ? hash(in) != m_value.value() : true;}

        [[nodiscard]] bool operator==(const std::size_t in) const {return isValid() ? m_value.value() == in : false;}
        [[nodiscard]] bool operator!=(const std::size_t in) const {return isValid() ? m_value.value() != in : true;}
        
    private:
        std::optional<std::size_t> m_value;
    };
}

#endif // TAILS_HANDLE_HPP
