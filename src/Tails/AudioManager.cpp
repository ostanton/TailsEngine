#include <Tails/AudioManager.hpp>
#include <Tails/AssetCache.hpp>
#include <Tails/SoundAsset.hpp>

namespace tails
{
void CAudioManager::playSound(const std::string& assetID)
    {
        if (const auto sound = CAssetCache::getAsset<CSoundAsset>(assetID))
            get().m_sound.setBuffer(*sound);

        get().m_sound.play();
    }

    void CAudioManager::playMusic(const std::string& path)
    {
        get().m_music.openFromFile(path);
        get().m_music.play();
    }
    
    CAudioManager& CAudioManager::get()
    {
        static CAudioManager instance;
        return instance;
    }
}
