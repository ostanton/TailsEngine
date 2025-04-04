#include <Tails/Assets/Loaders/SoundLoader.hpp>
#include <Tails/Assets/Sound.hpp>
#include <Tails/Assets/AssetRegistry.hpp>

namespace tails
{
    std::shared_ptr<IAsset> CSoundLoader::load()
    {
        return std::make_shared<CSound>();
    }
}
