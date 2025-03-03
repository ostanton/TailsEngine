#ifndef TAILS_TEXTURE_ASSET_HPP
#define TAILS_TEXTURE_ASSET_HPP

#ifdef TAILS_BACKEND_SFML3
#include <Platform/SFML3/Texture.hpp>
#elif defined(TAILS_BACKEND_NATIVE)
    #ifdef TAILS_OS_WIN32
        #include <Platform/Windows/Texture.hpp>
    #endif // TAILS_OS_WIN32
#else // TAILS_BACKEND_SFML3
#include <Tails/Assets/Asset.hpp>
#endif // TAILS_BACKEND_SFML3

namespace tails
{
#ifdef TAILS_BACKEND_SFML3
    using CTexture = sfml3::CTexture;
#elif defined(TAILS_BACKEND_NATIVE)
    #ifdef TAILS_OS_WIN32
        using CTexture = win32::CTexture;
    #endif // TAILS_OS_WIN32
#else // TAILS_BACKEND_SFML3
    class CTexture final : public IAsset
    {
        bool load(const std::filesystem::path& path) override {return false;}
    };
#endif // TAILS_BACKEND_SFML3
}

#endif // TAILS_TEXTURE_ASSET_HPP
