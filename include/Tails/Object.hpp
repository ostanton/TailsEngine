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
        enum EFlags
        {
            PendingCreate = 1 << 0,
            PendingDestroy = 1 << 1
        };
        
    public:
        CObject() = default;
        CObject(const CObject&) = default;
        CObject(CObject&&) = default;
        CObject& operator=(const CObject&) = default;
        CObject& operator=(CObject&&) = default;
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

        void clearFlags();

        [[nodiscard]] constexpr bool pendingCreate() const {return (m_flags & PendingCreate) == PendingCreate;}
        [[nodiscard]] constexpr bool pendingDestroy() const {return (m_flags & PendingDestroy) == PendingDestroy;}

    private:
        std::uint8_t m_flags {PendingCreate};
    };

    // Functions for creating children of CObject specifically

    /**
     * Creates a new object that is registered in the class registry, then casts it to the specified CObject subclass
     * @tparam T Object type
     * @param name Registered class name
     * @param outer The object this new object will reside in
     * @return Created object of specified type
     */
    template<Derives<CObject> T>
    T* newObject(std::string_view name, CObject* outer)
    {
        if (auto obj = constructClass<T>(name))
        {
            obj->outer = outer;
            return obj;
        }
        
        return nullptr;
    }

    /**
     * Creates a new object that is registered in the class registry
     * @param name Registered class name
     * @param outer The object this new object will reside in
     * @return Created object
     */
    inline CObject* newObject(std::string_view name, CObject* outer)
    {
        return newObject<CObject>(name, outer);
    }

    /**
     * Creates a new object, regardless of if it is registered in the class registry
     * @tparam T Object type
     * @tparam ArgsT Constructor argument types
     * @param outer The object this new object will reside in
     * @param args Constructor arguments
     * @return Created object
     */
    template<Derives<CObject> T, typename... ArgsT>
    requires ConstructibleUserType<T, ArgsT...>
    T* newObject(CObject* outer, ArgsT&&... args)
    {
        auto obj = new T(std::forward<ArgsT>(args)...);
        obj->outer = outer;
        return obj;
    }
}

#endif // TAILS_OBJECT_HPP
