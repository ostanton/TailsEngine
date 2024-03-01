#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include "TailsEngine/Debug/Debug.h"

namespace tails
{
class ResourceManager;
}

namespace tails
{
/**
 * \brief Generic asset manager class. Only meant to be used within the ResourceManager class, not by itself
 * \tparam AssetT The asset type (sf::Texture, sf::Font, sf::SoundBuffer, etc.)
 */
template<typename AssetT>
class AssetManager
{
    friend ResourceManager;

    std::unordered_map<std::string, std::unique_ptr<AssetT>> m_assets;
    
    void addAsset(const std::string& id, AssetT* asset)
    {
        // if we find 0 entries in the map
        if (m_assets.count(id) == 0)
            m_assets.emplace(std::make_pair(id, asset));
    }

public:
    /**
     * \brief Get an asset pointer with an id
     * \param id Identifier for this asset
     * \return Pointer to asset memory
     */
    AssetT* getAsset(const std::string& id)
    {
        // if we find 0 entries in the map
        if (m_assets.count(id) == 0)
        {
            Debug::log("AssetManager<AssetT>::getAsset() - Failed to get asset");
            return nullptr;
        }

        return m_assets.find(id)->second.get();
    }

    /**
     * \brief Get an asset reference with an id
     * \param id Identifier for this asset
     * \return Reference to asset memory
     */
    AssetT& getAssetRef(const std::string& id)
    {
        return *getAsset(id);
    }
};

}
