#include <Tails/AssetCache.hpp>
#include <Tails/TextureAsset.hpp>
#include <Tails/SoundAsset.hpp>
#include <Tails/FontAsset.hpp>
#include <Tails/Directories.hpp>

namespace tails
{
    std::shared_ptr<CTextureAsset> CAssetCache::loadTexture(const std::string& id, const std::string& path)
    {
        return loadAsset<CTextureAsset>(id, path);
    }

    std::shared_ptr<CSoundAsset> CAssetCache::loadSound(const std::string& id, const std::string& path)
    {
        return loadAsset<CSoundAsset>(id, path);
    }

    std::shared_ptr<CFontAsset> CAssetCache::loadFont(const std::string& id, const std::string& path)
    {
        return loadAsset<CFontAsset>(id, path);
    }

    std::shared_ptr<IAssetData> CAssetCache::getAsset(const std::string& id)
    {
        if (get().m_data.contains(id))
            return get().m_data[id].lock();

        CDebug::print("Failed to get asset, ID \"", id, "\" does not exist");
        return nullptr;
    }

    CAssetCache& CAssetCache::get()
    {
        static CAssetCache instance;
        return instance;
    }

    std::shared_ptr<IAssetData> CAssetCache::loadImpl(
        const std::string& id, const std::string& path, const std::shared_ptr<IAssetData>& data)
    {
        // TODO - debug print on fail load
        if (!data->load(CDirectories::getDirectory(data->getType()) + path))
        {
            // SFML has a print for this already, we're ok to not print this I think
            //CDebug::print("Failed to load path ", path);
            return nullptr;
        }
        
        if (get().m_data.contains(id))
        {
            if (!get().m_data[id].expired() || get().m_data[id].lock())
            {
                CDebug::print("Asset \"", id, "\" already exists, returning it as {type: ", get().m_data[id].lock()->getType(), "}");
                return get().m_data[id].lock();
            }

            // Contains the ID, but the data is invalid or null
            get().m_data[id] = data;
        }
        else
            get().m_data.try_emplace(id, data);

        CDebug::print("Loaded \"", id, "\" {type: ", data->getType(), ", path: \"", path, "\"}");
        
        return data;
    }
}
