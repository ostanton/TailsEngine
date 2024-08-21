#include <Tails/AssetCache.hpp>
#include <Tails/TextureAsset.hpp>
#include <Tails/SoundAsset.hpp>
#include <Tails/FontAsset.hpp>
#include <Tails/Directories.hpp>

namespace tails
{
    std::shared_ptr<CTextureAsset> CAssetCache::loadTexture(const std::string& id, const std::string& path)
    {
        return load<CTextureAsset>(id, path);
    }

    std::shared_ptr<CSoundAsset> CAssetCache::loadSound(const std::string& id, const std::string& path)
    {
        return load<CSoundAsset>(id, path);
    }

    std::shared_ptr<CFontAsset> CAssetCache::loadFont(const std::string& id, const std::string& path)
    {
        return load<CFontAsset>(id, path);
    }

    std::shared_ptr<IAssetData> CAssetCache::getAsset(const std::string& id)
    {
        if (get().m_data.contains(id))
            return get().m_data[id].lock();

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
            get().m_data[id] = data;
        else
            get().m_data.try_emplace(id, data);

        CDebug::print("Loaded \"", id, "\" {type: ", data->getType(), ", path: \"", path, "\"}");
        
        return data;
    }
}
