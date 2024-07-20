#ifndef TAILS_ASSETHANDLE_HPP
#define TAILS_ASSETHANDLE_HPP

#include <Tails/Config.hpp>

namespace tails
{
    /**
     * A wrapper around an integer for now.
     * Currently fails to compile (something to do with the standard xhash referencing a deleted function).
     */
    struct TAILS_API AssetHandle
    {
        using valueType = long long;
        
        AssetHandle() = default;
        AssetHandle(valueType id)
            : m_id(id) {}

        AssetHandle(const AssetHandle&) = default;
        AssetHandle(AssetHandle&&) = default;
        ~AssetHandle() = default;

        AssetHandle& operator=(const AssetHandle& other)
        {
            if (*this != other)
            {
                m_id = other.m_id;
            }

            return *this;
        }
        AssetHandle& operator=(AssetHandle&&) = default;
        AssetHandle& operator=(valueType id)
        {
            m_id = id;
            return *this;
        }

        bool operator==(const AssetHandle& other) const {return m_id == other.m_id;}
        bool operator!=(const AssetHandle& other) const {return !(*this == other);}

        AssetHandle operator+(const AssetHandle& other) const
        {
            return {m_id + other.m_id};
        }
        AssetHandle operator+(valueType other) const
        {
            return {m_id + other};
        }
        AssetHandle operator-(const AssetHandle& other) const
        {
            return {m_id - other.m_id};
        }
        AssetHandle operator-(valueType other) const
        {
            return {m_id - other};
        }

        AssetHandle& operator++()
        {
            ++m_id;
            return *this;
        }
        AssetHandle& operator++(int other)
        {
            m_id += other;
            return *this;
        }
        AssetHandle& operator--()
        {
            --m_id;
            return *this;
        }
        AssetHandle& operator--(int other)
        {
            m_id -= other;
            return *this;
        }

        AssetHandle& operator+=(const AssetHandle& other)
        {
            *this = *this + other;
            return *this;
        }
        AssetHandle& operator+=(valueType other)
        {
            m_id += other;
            return *this;
        }
        AssetHandle& operator-=(const AssetHandle& other)
        {
            *this = *this - other;
            return *this;
        }
        AssetHandle& operator-=(valueType other)
        {
            m_id -= other;
            return *this;
        }

    private:
        valueType m_id {0};
    };
}

#endif // TAILS_ASSETHANDLE_HPP
