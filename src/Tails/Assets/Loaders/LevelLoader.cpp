#include <Tails/Assets/Loaders/LevelLoader.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/Log.hpp>
#include <Tails/World/Level.hpp>

namespace tails::assets::level
{
    std::shared_ptr<IAsset> load(const CString& path)
    {
        auto level = assets::allocateAsset<CLevel>(path);
        if (!level)
        {
            TAILS_LOG_VA(AssetSubsystem, Error, "Failed to load level '{}'", path.getData());
            return nullptr;
        }
        
        level->loadFinished();
        TAILS_LOG_VA(AssetSubsystem, Message, "Loaded level '{}'", path.getData());
        return level;
    }

    std::shared_ptr<IAsset> load(u8* memory, usize size)
    {
        return nullptr;
    }
}
