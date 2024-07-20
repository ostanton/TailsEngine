#ifndef TAILS_OBJECT_HPP
#define TAILS_OBJECT_HPP

#include <Tails/Config.hpp>
#include <Tails/Assert.hpp>

#include <memory>

namespace tails
{
    class TAILS_API Object
    {
    public:
        // might want to default instead of delete these, but be weary of slicing!
        // as per C.67 of the C++ iso standard, might want these to be protected instead of deleted?
        Object() = default;
        Object(const Object&) = delete; // copy constructor
        Object(Object&&) = delete; // move constructor
        Object& operator=(const Object&) = delete; // copy assignment
        Object& operator=(Object&&) = delete; // move assignment
        virtual ~Object() = default;

        /**
         * Called as soon as this object is created after its outer has been set. For non-context-specific
         * things in which you need things like the outer, do them here
         */
        virtual void create() {}

        /**
         * Loop through the outers of this object until we find the outer of the specified type,
         * or until the outer is null (meaning this object has no outer)
         */
        template<typename T>
        T* getTypedOuter() const
        {
            static_assert(std::is_base_of_v<Object, T>,
                "Failed to get outer of specified type, it does not derive Object.");

            Object* pOuter {outer};

            while (pOuter)
            {
                if (auto typedOuter = dynamic_cast<T*>(pOuter))
                {
                    return typedOuter;
                }

                pOuter = pOuter->outer;
            }

            return nullptr;
        }

        void markForDestroy() {pendingDestroy = true;}

        Object* outer {nullptr};
        bool pendingCreate {true};
        bool pendingDestroy {false};
        // TODO - maybe hide these members and provide clear helper functions like markForDestroy()
    };

    // prefer std::make_unique over this if possible
    template<typename T>
    T* newObject(Object* outer)
    {
        static_assert(std::is_base_of_v<Object, T>,
                "Failed to create object of specified type, it does not derive Object.");
        TailsAssert(outer == nullptr, "New object must have a valid outer.");
        
        T* resultObj {new T};
        resultObj->outer = outer;
        resultObj->create();
        return resultObj;
    }

    template<typename T>
    std::unique_ptr<T> newObjectUnique(Object* outer)
    {
        static_assert(std::is_base_of_v<Object, T>,
                "Failed to create object of specified type, it does not derive Object.");
        TailsAssert(outer == nullptr, "New object must have a valid outer.");
        
        auto resultObj = std::make_unique<T>();
        resultObj->outer = outer;
        resultObj->create();
        return resultObj;
    }
}

#endif // TAILS_OBJECT_HPP
