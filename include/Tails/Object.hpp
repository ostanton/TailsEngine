#ifndef TAILS_OBJECT_HPP
#define TAILS_OBJECT_HPP

#include <Tails/Config.hpp>
#include <Tails/Serialisable.hpp>

#include <cstdint>
#include <string>

namespace tails
{
    class TAILS_API CObject : public ISerialisable
    {
        enum EObjectFlags
        {
            PendingCreate = 1 << 0,
            PendingDestroy = 1 << 1
        };
        
    public:
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

    template<typename T>
    using TUniqueObject = std::unique_ptr<T, void(*)(CObject*)>;

    CObject* newObject(std::string_view name, CObject* outer);
    TUniqueObject<CObject> newObjectUnique(std::string_view name, CObject* outer);
    void deleteObject(CObject* obj);

    template<typename T>
    T* newObjectOfType(std::string_view name, CObject* outer)
    {
        static_assert(std::is_base_of_v<CObject, T>,
            "Cannot create object, template type does not derive CObject.");
        
        return dynamic_cast<T*>(newObject(name, outer));
    }
    
    template<typename T>
    TUniqueObject<T> newObjectUniqueOfType(std::string_view name, CObject* outer)
    {
        return {newObjectOfType<T>(name, outer), deleteObject};
    }
}

#endif // TAILS_OBJECT_HPP
