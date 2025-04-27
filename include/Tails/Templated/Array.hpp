#ifndef TAILS_ARRAY_HPP
#define TAILS_ARRAY_HPP

#include <Tails/Core.hpp>
#include <Tails/Memory.hpp>
#include <Tails/Concepts.hpp>

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
            {
                resize(m_capacity * 2);
            }

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

        void resize(const usize capacity) noexcept
        {
            m_capacity = capacity;
            T* temp = m_ptr;
            m_ptr = mem::alloc<T>(m_capacity);
            for (usize i = 0; i < m_size; i++)
            {
                m_ptr[i] = temp[i];
            }
            mem::destroy(temp);
        }

    private:
        T* m_ptr;
        usize m_size;
        usize m_capacity;
    };
}

#endif // TAILS_ARRAY_HPP
