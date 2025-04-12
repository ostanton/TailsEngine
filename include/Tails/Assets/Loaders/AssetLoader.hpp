#ifndef TAILS_ASSET_LOADER_HPP
#define TAILS_ASSET_LOADER_HPP

#include <Tails/Core.hpp>

#include <memory>

namespace tails
{
    class IAsset;

    /**
     * Abstract base loader factory for creating and loading assets from various sources (filesystem, memory, etc.).
     * To create your own, inherit from this class, and override the pure functions with your own implementations.
     * Then, register it with the @code CAssetRegistry@endcode singleton, preferably in
     * @code IApplication::init()@endcode, like so:
     * @code
     * CAssetRegistry::get().registerFactory<CMyAssetFactory>(EMyAssetTypes::AssetType);
     * @endcode
     * You must also have your own enumeration for this, so the engine knows what asset "type" to assign
     * your custom factory to. All custom assets (everything to do with them) are assigned via the
     * @code EAssetType::Custom@endcode enumerator. Your custom asset type enumeration is simply added on
     * to the custom integer value. Look at @code EAssetType@endcode for more information.
     *
     * TODO - this could just be a free function, or a couple of free functions. The difference is:
     * 1. Polymorphism (this means dynamic allocation too, not super fun but oh well),
     * 2. State (factories can have state, and therefore keep tabs on created assets, etc. They really
     * shouldn't, but it's a thing),
     * 3. All sorts of private stuff (like helper functions, etc. This can be done easily with free
     * functions too though, just have the "factory" function in the header and the implementation
     * functions in the cpp),
     * 4. One factory, lots of functions (with single functions, you would need arrays for every kind
     * of loading. One array for "factory" functions loading from disk, one for memory, etc. With
     * a factory object you just add the object and those functions are all in that one context).
     * 
     * I'm torn between them. Oh well, let's just wait and see what other pros/cons I come up with!
     */
    class TAILS_API IAssetLoader
    {
    public:
        IAssetLoader() = default;
        // disallow copies and moving, factories should only live in the asset registry
        IAssetLoader(const IAssetLoader&) = delete;
        IAssetLoader(IAssetLoader&&) noexcept = delete;
        IAssetLoader& operator=(const IAssetLoader&) = delete;
        IAssetLoader& operator=(IAssetLoader&&) noexcept = delete;
        virtual ~IAssetLoader() = default;

        virtual std::shared_ptr<IAsset> load(const char* path) = 0;
    };
}

#endif // TAILS_ASSET_LOADER_HPP
