#include <Tails/Filesystem.hpp>

#include <SDL3/SDL_iostream.h>

namespace tails::fs
{
    u8* loadFile(const CString& path, usize* outSize)
    {
        auto const data = SDL_LoadFile(path.getData(), outSize);
        if (!data)
            return nullptr; // TODO - do we want error logs here or let the user display their own?

        return static_cast<u8*>(data);
    }
}
