#include <Tails/Memory.hpp>

#include <SDL3/SDL_stdinc.h>

namespace tails::mem
{
    void* alloc(const usize size)
    {
        return SDL_malloc(size);
    }

    void* allocAligned(const usize alignment, const usize size)
    {
        return SDL_aligned_alloc(alignment, size);
    }

    void freeT(void* ptr)
    {
        SDL_free(ptr);
    }

    void freeAligned(void* ptr)
    {
        SDL_aligned_free(ptr);
    }

    void* copy(void* destination, const void* source, const usize size)
    {
        return SDL_memcpy(destination, source, size);
    }

    i8 compare(const void* a, const void* b, const usize size)
    {
        return static_cast<i8>(SDL_memcmp(a, b, size));
    }

    void* set(void* target, const u8 value, const usize size)
    {
        return SDL_memset(target, value, size);
    }
}
