#ifndef TAILS_OBJECT_HPP
#define TAILS_OBJECT_HPP

#include <Tails/Config.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/ClassRegistry.hpp>

#include <cstdint>

namespace tails
{
    class TAILS_API CObject
    {
        enum EObjectFlags
        {
            PendingCreate = 1 << 0,
            PendingDestroy = 1 << 1
        };
        
    public:
        virtual ~CObject() = default;
        
        CObject* outer {nullptr};

        template<typename T>
        T* getTypedOuter() const
        {
            for (CObject* p_outer {outer}; p_outer; p_outer = p_outer->outer)
            {
                if (auto typedOuter = dynamic_cast<T*>(p_outer))
                    return typedOuter;
            }

            return nullptr;
        }

        void markForCreate();
        void unmarkForCreate();
        void markForDestroy();
        void unmarkForDestroy();

        [[nodiscard]] bool pendingCreate() const;
        [[nodiscard]] bool pendingDestroy() const;

    private:
        uint8_t m_flags {PendingCreate};
    };

    // Functions for creating children of CObject specifically

    CObject* newObject(std::string_view name, CObject* outer);

    template<DerivesObject T>
    T* newObject(std::string_view name, CObject* outer)
    {
        if (auto obj = constructClass<T>(name))
        {
            obj->outer = outer;
            return obj;
        }
        
        return nullptr;
    }

    template<DerivesObject T>
    T* newObject(CObject* outer)
    {
        auto obj = new T;
        obj->outer = outer;
        return obj;
    }
}

#endif // TAILS_OBJECT_HPP
