#include <Tails/Assets/Loaders/SoundLoader.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/Assets/Sound.hpp>

namespace tails::assets::sound
{
    std::shared_ptr<IAsset> load(const CString& path)
    {
        // TODO - load sound!
        return nullptr;
    }

    std::shared_ptr<IAsset> load(u8* memory, usize size)
    {
        return nullptr;
    }
}
