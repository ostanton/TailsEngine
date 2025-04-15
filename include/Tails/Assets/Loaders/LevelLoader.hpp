#ifndef TAILS_LEVEL_LOADER_HPP
#define TAILS_LEVEL_LOADER_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/Loaders/AssetLoader.hpp>

namespace tails
{
    class CLevel;

    /**
     * TODO - make different level loaders for different level types (LDtk, Tiled, etc.)
     */
    class TAILS_API CLevelLoader : public IAssetLoader
    {
    public:
        using AssetType = CLevel;

        std::shared_ptr<IAsset> load(const CString& path) override;
    };
}

#endif // TAILS_LEVEL_LOADER_HPP
