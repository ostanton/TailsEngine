#include <Tails/Assets/Loaders/SoundLoader.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>

namespace tails
{
    std::shared_ptr<IAsset> CSoundLoader::load(const CString& path)
    {
        // TODO - load sound!
        return assets::allocateAsset<CSound>(path);
    }
}
