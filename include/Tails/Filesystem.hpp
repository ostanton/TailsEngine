#ifndef TAILS_FILE_SYSTEM_HPP
#define TAILS_FILE_SYSTEM_HPP

#include <Tails/Core.hpp>
#include <Tails/String.hpp>

// Generic saving & loading functions, and working with the file system
// TODO - could have separate IO for saving/loading files? Then just use std::filesystem instead?
namespace tails::fs
{
    TAILS_API CString getCurrentDirectory();
    
    /**
     * Generic file loading function. Wraps SDL_LoadFile
     * @param path File path
     * @param outSize Size of the loaded file, NULL if not loaded
     * @return File data. nullptr if failed to load
     */
    TAILS_API u8* loadFile(const CString& path, usize* outSize);
}

#endif // TAILS_FILE_SYSTEM_HPP
