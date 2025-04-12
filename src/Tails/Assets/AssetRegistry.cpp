#include <Tails/Assets/AssetRegistry.hpp>
#include <Tails/Assets/Loaders/AssetLoader.hpp>
#include <Tails/Assets/AssetManager.hpp>

namespace tails
{
    CAssetRegistry& CAssetRegistry::get()
    {
        static CAssetRegistry instance;
        return instance;
    }

    std::shared_ptr<IAsset> CAssetRegistry::loadAssetFromFile(
        const u8 assetType,
        const char* filename,
        CAssetManager& assetManager
    ) const
    {
        if (m_factories.find(assetType) == m_factories.end())
            return nullptr; // TODO - log error message

        const auto result = m_factories.at(assetType)->load(filename);
        assetManager.addAsset(result);
        return result;
    }

    void CAssetRegistry::registerFactoryImpl(std::unique_ptr<IAssetLoader> factory, const u8 assetType)
    {
        m_factories.try_emplace(assetType, std::move(factory));
    }
}
