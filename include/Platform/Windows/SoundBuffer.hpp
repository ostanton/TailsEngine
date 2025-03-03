#ifndef TAILS_WIN32_SOUND_BUFFER_ASSET_HPP
#define TAILS_WIN32_SOUND_BUFFER_ASSET_HPP

#include <Tails/Assets/Asset.hpp>

namespace tails::win32
{
    class CSoundBuffer final : public IAsset
    {
        bool load(const std::filesystem::path& path) override
        {
            return true;
        }
    };
}

#endif // TAILS_WIN32_SOUND_BUFFER_ASSET_HPP
