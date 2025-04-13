#include <Tails/Assets/AssetRegistry.hpp>
#include <Tails/Assets/Loaders/AssetLoader.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/Log.hpp>

namespace tails::impl
{
    CAssetRegistry& CAssetRegistry::get()
    {
        static CAssetRegistry instance;
        return instance;
    }

    std::shared_ptr<IAsset> CAssetRegistry::loadAssetFromFile(
        const u8 assetType,
        const char* filename
    ) const
    {
        if (m_factories.find(assetType) == m_factories.end())
        {
            TAILS_LOG(AssetRegistry, Error, "Failed to find asset loader");
            return nullptr;
        }

        auto result = m_factories.at(assetType)->load(filename);
        
        if (!result)
        {
            TAILS_LOG_VA(AssetRegistry, Error, "Failed to load asset path '%s'", filename);
            return nullptr;
        }
        
        assets::addAsset(result);
        return result;
    }

    void CAssetRegistry::registerLoaderImpl(
        std::unique_ptr<IAssetLoader> factory,
        const u8 assetType,
        const char* debugName
    )
    {
        m_factories.try_emplace(assetType, std::move(factory));
        TAILS_LOG_VA(AssetRegistry, Message, "Registered asset loader '%s'", debugName);
    }
}
