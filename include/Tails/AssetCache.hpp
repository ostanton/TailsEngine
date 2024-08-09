#ifndef TAILS_ASSETCACHE_HPP
#define TAILS_ASSETCACHE_HPP

#include <Tails/Config.hpp>

#include <unordered_map>
#include <string>
#include <memory>
#include <functional>

namespace tails
{
    class IAssetData;
    class CTextureAsset;
    class CSoundAsset;
    
    class TAILS_API CAssetCache final
    {
        using DataMap = std::unordered_map<std::string, std::weak_ptr<IAssetData>>;
        
    public:
        static std::shared_ptr<CTextureAsset> loadTexture(const std::string& id, const std::string& path);
        static std::shared_ptr<CSoundAsset> loadSound(const std::string& id, const std::string& path);

        template<typename T>
        static std::shared_ptr<T> load(const std::string& id, const std::string& path)
        {
            static_assert(std::is_base_of_v<IAssetData, T>, "Failed to load asset, it does not derive IAssetData.");

            auto deleter = [&](const std::string& name)
            {
                if (!get().m_data.contains(name)) return;
                
                if (get().m_data[name].expired())
                    get().m_data.erase(name);
            };

            std::shared_ptr<T> data {new T, std::bind(deleter, id)};
            
            return std::static_pointer_cast<T>(loadImpl(id, path, data));
        }

        [[nodiscard]] static std::shared_ptr<IAssetData> getAsset(const std::string& id);

        template<typename T>
        [[nodiscard]] static std::shared_ptr<T> getAsset(const std::string& id)
        {
            static_assert(std::is_base_of_v<IAssetData, T>, "Failed to get asset, it does not derive IAssetData.");
            
            return std::static_pointer_cast<T>(getAsset(id));
        }
        
    private:
        [[nodiscard]] static CAssetCache& get();
        
        static std::shared_ptr<IAssetData> loadImpl(
            const std::string& id, const std::string& path, const std::shared_ptr<IAssetData>& data);
        
        DataMap m_data;
    };
}

#endif // TAILS_ASSETCACHE_HPP
