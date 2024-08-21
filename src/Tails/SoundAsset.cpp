#include <Tails/SoundAsset.hpp>

namespace tails
{
    bool CSoundAsset::load(const std::string& path)
    {
        return loadFromFile(path);
    }

    std::string CSoundAsset::getType() const
    {
        return "sound";
    }
}
