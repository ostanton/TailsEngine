#ifndef TAILS_STATIC_ARRAY_HPP
#define TAILS_STATIC_ARRAY_HPP

#include <Tails/Core.hpp>

#include <initializer_list>

namespace tails
{
    template<typename T, usize Size>
    class TStaticArray final
    {
    public:
        struct SIterator
        {
            SIterator(T* inPtr)
                : ptr(inPtr)
            {}

            [[nodiscard]] T& operator*() const {return *ptr;}
            [[nodiscard]] T* operator->() const {return ptr;}

            [[nodiscard]] bool operator==(const SIterator& other) const {return ptr == other.ptr;}
            [[nodiscard]] bool operator!=(const SIterator& other) const {return !(*this == other);}

            SIterator& operator++() {++ptr; return *this;}
            SIterator operator++(int)
            {
                SIterator tmp = *this;
                ++ptr;
                return tmp;
            }
            
            T* ptr;
        };
        
        TStaticArray() = default;
        TStaticArray(const std::initializer_list<T>& list)
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
        TStaticArray(const TStaticArray&) = default;
        TStaticArray(TStaticArray&&) noexcept = default;
        TStaticArray& operator=(const TStaticArray&) = default;
        TStaticArray& operator=(TStaticArray&&) noexcept = default;
        ~TStaticArray() = default;

        [[nodiscard]] T& operator[](const usize index) noexcept {return m_array[index];}
        [[nodiscard]] const T& operator[](const usize index) const noexcept {return m_array[index];}

        [[nodiscard]] usize size() const noexcept {return Size;}

        [[nodiscard]] SIterator begin() noexcept {return m_array;}
        [[nodiscard]] SIterator end() noexcept {return &m_array[Size];}
        
    private:
        T m_array[Size];
    };
}

#endif // TAILS_STATIC_ARRAY_HPP
