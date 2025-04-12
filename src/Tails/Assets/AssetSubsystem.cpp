#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/Assets/AssetRegistry.hpp>
#include <Tails/Assets/Loaders/TextureLoader.hpp>
#include <Tails/Assets/Loaders/SoundLoader.hpp>

namespace tails::assets
{
    void init()
    {
        // register default engine asset loaders
        auto& registry = impl::CAssetRegistry::get();
        registry.registerLoader<CTextureLoader>(getAssetType(EAssetType::Texture));
        registry.registerLoader<CSoundLoader>(getAssetType(EAssetType::Sound));
    }
}
