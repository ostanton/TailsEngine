#include <Tails/Audio/MusicBus.hpp>
#include <Tails/Assets/AssetInfo.hpp>
#include <Tails/Assets/Metadata/AssetMetadata.hpp>

namespace tails
{
    void MusicBus::setAsset(const AssetInfo& asset)
    {
        m_music.openFromFile(asset.getPath());
    }

    void MusicBus::play()
    {
        m_music.play();
    }

    void MusicBus::pause()
    {
        m_music.pause();
    }

    void MusicBus::stop()
    {
        m_music.stop();
    }

    void MusicBus::setVolume(float volume)
    {
        Bus::setVolume(volume);

        m_music.setVolume(volume * 100.f);
    }
} // tails
