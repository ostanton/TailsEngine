#include <Tails/Assets/Loaders/LevelLoader.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/World/Level.hpp>
#include <Tails/Log.hpp>

namespace tails
{
    std::shared_ptr<IAsset> CLevelLoader::load(const CString& path)
    {
        auto level = assets::allocateAsset<CLevel>(path);
        if (!level)
        {
            TAILS_LOG_VA(AssetSubsystem, Error, "Failed to load level '%s'", path.getData());
            return nullptr;
        }
        
        level->loadFinished();
        return level;
    }
}
