#ifndef TAILS_FONT_ASSET_HPP
#define TAILS_FONT_ASSET_HPP

#ifdef TAILS_BACKEND_SFML3
    #include <Platform/SFML3/Font.hpp>
#elif defined(TAILS_BACKEND_NATIVE)
    #ifdef TAILS_OS_WIN32
        #include <Platform/Windows/Font.hpp>
    #endif // TAILS_OS_WIN32
#else // TAILS_BACKEND_SFML3
    #include <Tails/Assets/Asset.hpp>
#endif // TAILS_BACKEND_SFML3

namespace tails
{
#ifdef TAILS_BACKEND_SFML3
    using CFont = sfml3::CFont;
#elif defined(TAILS_BACKEND_NATIVE)
    #ifdef TAILS_OS_WIN32
        using CFont = win32::CFont;
    #endif // TAILS_OS_WIN32
#else // TAILS_BACKEND_SFML3
    class CFont final : public IAsset
    {
        bool load(const std::filesystem::path& path) override {return false;}
    };
#endif // TAILS_BACKEND_SFML3
}

#endif // TAILS_FONT_ASSET_HPP
