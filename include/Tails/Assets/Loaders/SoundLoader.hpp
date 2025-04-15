#ifndef TAILS_SOUND_LOADER_HPP
#define TAILS_SOUND_LOADER_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/Loaders/AssetLoader.hpp>

namespace tails
{
    class CSound;
    
    class TAILS_API CSoundLoader : public IAssetLoader
    {
    public:
        using AssetType = CSound;
        
        std::shared_ptr<IAsset> load(const CString& path) override;
    };
}

#endif // TAILS_SOUND_LOADER_HPP
