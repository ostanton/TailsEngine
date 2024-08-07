#include <Tails/AssetCache.hpp>
#include <Tails/TextureAsset.hpp>

namespace tails
{
    std::shared_ptr<CTextureAsset> CAssetCache::loadTexture(const std::string& id, const std::string& path)
    {
        return load<CTextureAsset>(id, path);
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
        data->load(path);
        
        if (get().m_data.contains(id))
            get().m_data[id] = data;
        else
            get().m_data.try_emplace(id, data);
        
        return data;
    }
}
