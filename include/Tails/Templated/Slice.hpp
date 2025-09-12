#ifndef TAILS_SLICE_HPP
#define TAILS_SLICE_HPP

#include <Tails/Core.hpp>

namespace tails
{
    template<typename T>
    class TSlice final
    {
    public:
        constexpr TSlice() noexcept = default;
        constexpr TSlice(T* ptr, const usize length) noexcept
            : m_ptr(ptr), m_size(length)
        {}
        template<typename ItT>
        constexpr TSlice(ItT begin, ItT end) noexcept
            : m_ptr(begin.ptr), m_size(end - begin)
        {}
        constexpr TSlice(const TSlice& other) noexcept = default;
        constexpr TSlice(TSlice&& other) noexcept = default;
        constexpr TSlice& operator=(const TSlice& other) noexcept = default;
        constexpr TSlice& operator=(TSlice&& other) noexcept = default;
        constexpr ~TSlice() noexcept = default;

        [[nodiscard]] constexpr auto operator<=>(const TSlice&) const noexcept = default;

        [[nodiscard]] constexpr usize size() const noexcept {return m_size;}

        [[nodiscard]] constexpr T& operator[](const usize index) noexcept {return m_ptr[index];}
        [[nodiscard]] constexpr const T& operator[](const usize index) const noexcept {return m_ptr[index];}

    private:
        T* m_ptr {nullptr};
        usize m_size {0};
    };
}

#endif // TAILS_SLICE_HPP
