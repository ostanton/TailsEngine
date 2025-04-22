#ifndef TAILS_MEMORY_HPP
#define TAILS_MEMORY_HPP

#include <Tails/Core.hpp>

#include <utility>

/**
 * Memory-related functions which wrap SDL3's memory functions, providing platform-agnostic functionality
 */
namespace tails::mem
{
    /**
     * Allocates an amount of uninitialised data dynamically (generally via the heap).
     * Must be freed/destroyed with mem::freeT() or mem::destroy()
     * @param size Number of bytes to allocate
     * @return Pointer to allocated data
     */
    void* alloc(usize size);
    void* allocAligned(usize alignment, usize size);

    /**
     * Allocates a number of objects of type T dynamically (generally via the heap).
     * Must be freed/destroyed with mem::freeT() or mem::destroy()
     * @tparam T Type to allocate
     * @param num Number of objects to allocate
     * @return Pointer to allocated data
     */
    template<typename T>
    T* alloc(const usize num = 1)
    {
        return static_cast<T*>(alloc(num * sizeof(T)));
    }

    template<typename T>
    T* allocAligned(const usize alignment = alignof(T), const usize num = 1)
    {
        return static_cast<T*>(allocAligned(alignment, sizeof(T) * num));
    }

    /**
     * Frees allocated memory
     * @param ptr Pointer to allocated memory, can be nullptr
     */
    void freeT(void* ptr);
    void freeAligned(void* ptr);

    /**
     * Calls the constructor for the given object via placement new
     * @tparam T Type to construct
     * @tparam ArgsT Constructor argument types
     * @param obj Object to construct
     * @param args Constructor arguments
     */
    template<typename T, typename... ArgsT>
    constexpr void construct(T& obj, ArgsT&&... args)
    {
        new (&obj) T(std::forward<ArgsT>(args)...);
    }

    /**
     * Allocates an object of type T and calls its constructor with the given arguments.
     * Essentially a substitute for "new"
     * @tparam T Object type
     * @tparam ArgsT Constructor argument types
     * @param args Constructor arguments
     * @return Allocated object
     */
    template<typename T, typename... ArgsT>
    constexpr T* newObject(ArgsT&&... args)
    {
        auto const ptr = alloc<T>();
        construct(*ptr, std::forward<ArgsT>(args)...);
        return ptr;
    }

    /**
     * Calls the destructor for the given object
     * @tparam T Object type
     * @param obj Object to destruct
     */
    template<typename T>
    void destruct(T* obj)
    {
        if constexpr (!std::is_destructible_v<T>)
            return;
        
        if (!obj)
            return;

        obj->~T();
    }

    /**
     * Calls the destructor for the given object and frees its memory
     * @tparam T Object type
     * @param obj Object to destroy
     */
    template<typename T>
    void destroy(T* obj)
    {
        destruct(obj);
        freeT(obj);
    }

    /**
     * Copies source memory into target memory
     * @param destination Target memory
     * @param source Source memory
     * @param size Size of the memory
     * @return Target memory
     */
    void* copy(void* destination, const void* source, usize size);

    /**
     * Copies source memory into target memory
     * @tparam T Data type
     * @param destination Target memory
     * @param source Source memory
     * @return Target memory
     */
    template<typename T>
    T* copy(T* destination, const T* source)
    {
        return static_cast<T*>(copy(destination, source, sizeof(T)));
    }

    i8 compare(const void* a, const void* b, usize size);

    template<typename T>
    i8 compare(const T* a, const T* b)
    {
        return compare(a, b, sizeof(T));
    }

    /**
     * Sets the target memory of specified size to the specified value
     * @param target Target memory to set
     * @param value Byte value to set target to
     * @param size Size of the target memory in bytes
     * @return The target memory
     */
    void* set(void* target, u8 value, usize size);

    /**
     * Sets the target memory to the specified value
     * @tparam T Data type
     * @param target Target memory to set
     * @param value Byte value to set target to
     * @return The target memory
     */
    template<typename T>
    T* set(T* target, const u8 value)
    {
        return static_cast<T*>(set(target, value, sizeof(T)));
    }
}

#endif // TAILS_MEMORY_HPP
