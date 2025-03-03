#ifndef TAILS_SOUND_BUFFER_HPP
#define TAILS_SOUND_BUFFER_HPP

#ifdef TAILS_BACKEND_SFML3
#include <Platform/SFML3/SoundBuffer.hpp>
#elif defined(TAILS_BACKEND_NATIVE)
    #ifdef TAILS_OS_WIN32
        #include <Platform/Windows/SoundBuffer.hpp>
    #endif // TAILS_OS_WIN32
#else // TAILS_BACKEND_SFML3
#include <Tails/Assets/Asset.hpp>
#endif // TAILS_BACKEND_SFML3

namespace tails
{
#ifdef TAILS_BACKEND_SFML3
    using CSoundBuffer = sfml3::CSoundBuffer;
#elif defined(TAILS_BACKEND_NATIVE)
    #ifdef TAILS_OS_WIN32
        using CSoundBuffer = win32::CSoundBuffer;
    #endif // TAILS_OS_WIN32
#else // TAILS_BACKEND_SFML3
    class CSoundBuffer final : public IAsset
    {
        bool load(const std::filesystem::path& path) override {return false;}
    };
#endif // TAILS_BACKEND_SFML3
}

#endif // TAILS_SOUND_BUFFER_HPP
