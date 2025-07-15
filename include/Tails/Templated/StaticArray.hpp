#ifndef TAILS_STATIC_ARRAY_HPP
#define TAILS_STATIC_ARRAY_HPP

#include <Tails/Core.hpp>

#include <initializer_list>

namespace tails
{
    /**
     * A simple static array
     * @tparam T Element type
     * @tparam Size Array size
     */
    template<typename T, usize Size>
    class TStaticArray final
    {
    public:
        using ElementType = T;

        struct SIterator
        {
            constexpr SIterator(T* inPtr)
                : ptr(inPtr)
            {}

            [[nodiscard]] constexpr T& operator*() const {return *ptr;}
            [[nodiscard]] constexpr T* operator->() const {return ptr;}

            [[nodiscard]] constexpr bool operator==(const SIterator& other) const {return ptr == other.ptr;}
            [[nodiscard]] constexpr bool operator!=(const SIterator& other) const {return !(*this == other);}

            constexpr SIterator& operator++() {++ptr; return *this;}
            constexpr SIterator operator++(int)
            {
                SIterator tmp = *this;
                ++ptr;
                return tmp;
            }
            
            T* ptr;
        };
        
        constexpr TStaticArray() = default;
        constexpr TStaticArray(const std::initializer_list<T>& list)
        {
            if (list.size() > Size)
                return;
            
            usize i {0};
            for (const auto& item : list)
            {
                m_array[i] = item;
                i++;
            }
        }
        constexpr TStaticArray(const TStaticArray&) = default;
        constexpr TStaticArray(TStaticArray&&) noexcept = default;
        constexpr TStaticArray& operator=(const TStaticArray&) = default;
        constexpr TStaticArray& operator=(TStaticArray&&) noexcept = default;
        constexpr ~TStaticArray() = default;

        [[nodiscard]] constexpr T& operator[](const usize index) noexcept {return m_array[index];}
        [[nodiscard]] constexpr const T& operator[](const usize index) const noexcept {return m_array[index];}

        [[nodiscard]] constexpr usize size() const noexcept {return Size;}

        [[nodiscard]] constexpr SIterator begin() noexcept {return m_array;}
        [[nodiscard]] constexpr SIterator end() noexcept {return &m_array[Size];}
        
    private:
        T m_array[Size];
    };
}

#endif // TAILS_STATIC_ARRAY_HPP
