#ifndef TAILS_ASSET_REGISTRY_HPP
#define TAILS_ASSET_REGISTRY_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/AssetType.hpp>

#include <memory>
#include <unordered_map>

namespace tails
{
    class IAssetLoader;
    class IAsset;
    class CAssetManager;
    
    /**
     * The asset registry is a central repository of registered asset factories which the asset manager
     * queries to create assets. It works on the same ID system the manager does. Read up on it there.
     *
     * TODO - could have auto-registering at static-time:
     * https://stackoverflow.com/questions/10676498/factory-pattern-allocating-memory-at-compile-time-and-how-to-print-compile-time
     */
    class TAILS_API CAssetRegistry final
    {
        friend CAssetManager;
        
    public:
        static CAssetRegistry& get();

        template<typename FactoryT, typename CustomAssetTypeT>
        void registerFactory(const CustomAssetTypeT customAssetType)
        {
            registerFactoryImpl(
                std::make_unique<FactoryT>(),
                getCustomAssetID(customAssetType)
            );
        }

        std::shared_ptr<IAsset> loadAssetFromFile(EAssetType assetType, const char* filename) const;
        template<typename CustomAssetTypeT>
        std::shared_ptr<IAsset> loadAssetFromFile(const CustomAssetTypeT customAssetType, const char* filename) const
        {
            return loadAssetFromFileImpl(
                getCustomAssetID(customAssetType),
                filename
            );
        }

    private:
        CAssetRegistry() = default;

        template<typename FactoryT>
        void registerEngineFactory(const EAssetType assetType)
        {
            registerFactoryImpl(std::make_unique<FactoryT>(), static_cast<u8>(assetType));
        }
        
        void registerFactoryImpl(std::unique_ptr<IAssetLoader> factory, u8 assetID);

        std::shared_ptr<IAsset> loadAssetFromFileImpl(u8 assetID, const char* filename) const;

        std::unordered_map<u8, std::unique_ptr<IAssetLoader>> m_factories;
    };

    template<typename FactoryT>
    class TAILS_API TCustomAssetRegistrar
    {
    public:
        template<typename CustomAssetTypeT>
        TCustomAssetRegistrar(CustomAssetTypeT customAssetType)
        {
            CAssetRegistry::get().registerFactory<FactoryT>(customAssetType);
        }
    };
}

// TODO - auto register asset loaders
#define TAILS_REGISTER_CUSTOM_ASSET_LOADER(LOADER_CLASS, CUSTOM_ASSET_TYPE) \
    static inline ::tails::TCustomAssetRegistrar<LOADER_CLASS> gRegistrar##LOADER_CLASS {CUSTOM_ASSET_TYPE};

#endif // TAILS_ASSET_REGISTRY_HPP
