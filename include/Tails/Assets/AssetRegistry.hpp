#ifndef TAILS_ASSET_REGISTRY_HPP
#define TAILS_ASSET_REGISTRY_HPP

#include <Tails/Core.hpp>

#include <memory>
#include <unordered_map>

namespace tails
{
    class IAssetLoader;
    class IAsset;

    namespace impl
    {
        /**
         * The asset registry is a central repository of registered asset factories which the asset manager
         * queries to create assets. It works on the same ID system the manager does. Read up on it there
         */
        class TAILS_API CAssetRegistry final
        {
        public:
            static CAssetRegistry& get();

            template<typename FactoryT>
            void registerLoader(const u8 assetType)
            {
                registerLoaderImpl(
                    std::make_unique<FactoryT>(),
                    assetType,
                    typeid(FactoryT).name()
                );
            }

            std::shared_ptr<IAsset> loadAssetFromFile(
                u8 assetType,
                const char* filename
            ) const;

        private:
            CAssetRegistry() = default;

            void registerLoaderImpl(
                std::unique_ptr<IAssetLoader> factory,
                u8 assetType,
                const char* debugName
            );

            std::unordered_map<u8, std::unique_ptr<IAssetLoader>> m_factories;
        };

        template<typename FactoryT>
        struct TAssetRegistryEntry final
        {
            explicit TAssetRegistryEntry(const u8 customAssetType)
            {
                CAssetRegistry::get().registerLoader<FactoryT>(customAssetType);
            }
        };
    }
}

// TODO - fixup! Does not work when called in Tails library cpp files!!
#define TAILS_REGISTER_ASSET_LOADER(CLASS, ASSET_TYPE) \
    template<typename> struct TAssetLoaderRegistration; \
    template<> struct TAssetLoaderRegistration<CLASS> \
    { \
        static const ::tails::impl::TAssetRegistryEntry<CLASS> gAssetRegistrar; \
    }; \
    const ::tails::impl::TAssetRegistryEntry<CLASS> TAssetLoaderRegistration<CLASS>::gAssetRegistrar {::tails::getAssetType(ASSET_TYPE)};

#endif // TAILS_ASSET_REGISTRY_HPP
