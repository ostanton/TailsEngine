#ifndef TAILS_OBJECT_HPP
#define TAILS_OBJECT_HPP

#include <Tails/Config.hpp>

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
        uint8 m_flags {PendingCreate};
    };
}

#endif // TAILS_OBJECT_HPP
