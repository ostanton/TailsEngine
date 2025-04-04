#ifndef TAILS_SOUND_LOADER_HPP
#define TAILS_SOUND_LOADER_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/Loaders/AssetLoader.hpp>

namespace tails
{
    class TAILS_API CSoundLoader : public IAssetLoader
    {
    public:
        std::shared_ptr<IAsset> load() override;
    };
}

#endif // TAILS_SOUND_LOADER_HPP
