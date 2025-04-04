#include <Tails/Assets/AssetRegistry.hpp>
#include <Tails/Assets/Loaders/AssetLoader.hpp>

namespace tails
{
    CAssetRegistry& CAssetRegistry::get()
    {
        static CAssetRegistry instance;
        return instance;
    }

    std::shared_ptr<IAsset> CAssetRegistry::loadAssetFromFile(
        const EAssetType assetType,
        const char* filename
    ) const
    {
        return loadAssetFromFileImpl(static_cast<u8>(assetType), filename);
    }

    void CAssetRegistry::registerFactoryImpl(std::unique_ptr<IAssetLoader> factory, const u8 assetID)
    {
        m_factories.try_emplace(assetID, std::move(factory));
    }

    std::shared_ptr<IAsset> CAssetRegistry::loadAssetFromFileImpl(const u8 assetID, const char* filename) const
    {
        return m_factories.at(assetID)->load(); // TODO - load from file, specifics
    }
}
