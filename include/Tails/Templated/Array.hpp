#ifndef TAILS_ARRAY_HPP
#define TAILS_ARRAY_HPP

#include <Tails/Core.hpp>
#include <Tails/Memory.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/Maths/Maths.hpp>

#include <initializer_list>

namespace tails
{
    /**
     * Dynamically-allocated array
     * @tparam T Array type
     */
    template<typename T>
    class TArray final
    {
    public:
        TArray()
            : m_ptr(mem::alloc<T>()), m_size(0), m_capacity(1)
        {}
        TArray(const usize capacity)
            : m_ptr(mem::alloc<T>(capacity)), m_size(0), m_capacity(capacity)
        {}
        TArray(const std::initializer_list<T>& list)
            : m_ptr(mem::alloc<T>(list.size())), m_size(list.size()), m_capacity(list.size())
        {
            usize i {0};
            for (const auto& item : list)
            {
                m_ptr[i] = item;
                i++;
            }
        }
        TArray(const TArray&) = default;
        TArray(TArray&&) noexcept = default;
        TArray& operator=(const TArray&) = default;
        TArray& operator=(TArray&&) noexcept = default;
        ~TArray()
        {
            mem::destroy(m_ptr);
        }

        T* add(const T& element)
        {
            if (m_size >= m_capacity)
                resize(m_capacity * 2);

            m_ptr[m_size] = element;
            m_size++;
            return &m_ptr[m_size - 1];
        }

        template<typename... ArgsT>
        requires ConstructibleFrom<T, ArgsT...>
        T* emplace(ArgsT&&... args)
        {
            if (m_size >= m_capacity)
            {
                resize(m_capacity * 2);
            }

            mem::construct(m_ptr[m_size], std::forward<ArgsT>(args)...);
            m_size++;
            return &m_ptr[m_size - 1];
        }

        void removeAt(const usize index) noexcept
        {
            if (index >= m_size)
                return;

            // TODO
        }

        [[nodiscard]] usize size() const noexcept {return m_size;}
        void clear() {m_size = 0;}

        void resize(const usize capacity) noexcept
        {
            T* newPtr {mem::alloc<T>(capacity)};
            const usize minSize {maths::min(m_size, capacity)};
            for (usize i {0}; i < minSize; i++)
            {
                newPtr[i] = m_ptr[i];
            }

            mem::destroy(m_ptr);
            m_ptr = newPtr;
            m_size = minSize;
            m_capacity = capacity;
        }

        template<Predicate<const T&, const T&> PredT>
        void sort(PredT predicate)
        {
            const T* lastItem {nullptr};
            for (usize i; i < m_size; i++)
            {
                if (!lastItem)
                    continue;

                if (predicate(*lastItem, m_ptr[i]))
                {
                    // TODO
                }

                lastItem = &m_ptr[i];
            }
        }

        T& operator[](const usize index) noexcept {return m_ptr[index];}
        const T& operator[](const usize index) const noexcept {return m_ptr[index];}

    private:
        T* m_ptr;
        usize m_size;
        usize m_capacity;
    };
}

#endif // TAILS_ARRAY_HPP
