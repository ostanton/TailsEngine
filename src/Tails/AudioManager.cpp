#include <Tails/AudioManager.hpp>
#include <Tails/AssetCache.hpp>
#include <Tails/SoundAsset.hpp>

namespace tails
{/*
    void CAudioManager::playSound()
    {
        if (get().m_sound.getBuffer())
            get().m_sound.play();
    }

    void CAudioManager::playSound(const std::string& assetID)
    {
        playSound(CAssetCache::getAsset<CSoundAsset>(assetID));
    }

    void CAudioManager::playSound(std::shared_ptr<CSoundAsset> asset)
    {
        if (asset) get().m_currentSound = asset;

        get().m_sound.setBuffer(*get().m_currentSound);

        playSound();
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
    }*/
}
