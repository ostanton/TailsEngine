#ifndef TAILS_OBJECT_HPP
#define TAILS_OBJECT_HPP

#include <memory>

namespace tails
{
    class Object
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

        template<typename T>
        T* getTypedOuter()
        {
            return static_cast<T*>(outer);
        }

        Object* outer {nullptr};

    protected:
        virtual void create() {}

        bool pendingCreate {true};
        bool pendingDestroy {false};
    };

    // prefer std::make_unique over this if possible
    template<typename T>
    T* newObject(Object* outer)
    {
        Object* resultObj {new T};
        resultObj->outer = outer;
        resultObj->create();
        return resultObj;
    }

    template<typename T>
    std::unique_ptr<T> newObjectUnique(Object* outer)
    {
        std::unique_ptr<Object> resultObj {std::make_unique<T>()};
        resultObj->outer = outer;
        resultObj->create();
        return std::move(resultObj);
    }
}

#endif // TAILS_OBJECT_HPP
