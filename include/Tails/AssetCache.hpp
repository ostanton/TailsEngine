#ifndef TAILS_ASSETCACHE_HPP
#define TAILS_ASSETCACHE_HPP

#include <Tails/Config.hpp>
#include <Tails/Debug.hpp>

#include <unordered_map>
#include <string>
#include <memory>
#include <functional>

namespace tails
{
    class IAssetData;
    class CTextureAsset;
    class CSoundAsset;
    class CFontAsset;
    
    class TAILS_API CAssetCache final
    {
        using DataMap = std::unordered_map<std::string, std::weak_ptr<IAssetData>>;
        
    public:
        /**
         * Loads a texture asset from file, or gets it if the ID exists and the asset is valid.
         * @param id The asset's unique identifier
         * @param path Where to find the asset in relation to CDirectories' set directories
         */
        static std::shared_ptr<CTextureAsset> loadTexture(const std::string& id, const std::string& path);

        /**
         * Loads a sound (one shot, not music) asset from file, or gets it if the ID exists and the asset is valid.
         * @param id The asset's unique identifier
         * @param path Where to find the asset in relation to CDirectories' set directories
         */
        static std::shared_ptr<CSoundAsset> loadSound(const std::string& id, const std::string& path);

        /**
         * Loads a font asset from file, or gets it if the ID exists and the asset is valid.
         * @param id The asset's unique identifier
         * @param path Where to find the asset in relation to CDirectories' set directories
         */
        static std::shared_ptr<CFontAsset> loadFont(const std::string& id, const std::string& path);

        /**
         * Loads an asset from file, or gets it if the ID exists and the asset is valid.
         * @param id The asset's unique identifier
         * @param path Where to find the asset in relation to CDirectories' set directories
         * @tparam T The asset type to load
         */
        template<typename T>
        static std::shared_ptr<T> loadAsset(const std::string& id, const std::string& path)
        {
            static_assert(std::is_base_of_v<IAssetData, T>, "Failed to load asset, it does not derive IAssetData.");

            // Asset deleter, erases the map entry when the last shared_ptr is deleted.
            auto deleter = [&](const std::string& name)
            {
                if (!get().m_data.contains(name)) return;
                
                if (get().m_data[name].expired())
                {
                    get().m_data.erase(name);
                    CDebug::print("Erased asset \"", name, "\"");
                }
            };

            // Create the shared_ptr object to use the deleter, and pass to implementation function
            // to be added to the map
            std::shared_ptr<T> data {new T, std::bind(deleter, id)};
            
            return std::static_pointer_cast<T>(loadImpl(id, path, data));
        }

        /**
         * Gets the asset of ID if valid.
         * @param id The asset's unique identifier
         */
        [[nodiscard]] static std::shared_ptr<IAssetData> getAsset(const std::string& id);

        /**
         * Gets the asset of ID if valid and casts it to the specified type.
         * @param id The asset's unique identifier
         */
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
