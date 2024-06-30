#include <Tails/Audio/SoundBus.hpp>
#include <Tails/Assets/AssetInfo.hpp>
#include <Tails/Assets/SoundResource.hpp>
#include <Tails/Assets/Metadata/SoundMetadata.hpp>

namespace tails
{
    void SoundBus::setAsset(const AssetInfo& asset)
    {
        m_sound.setBuffer(*asset.getResource<Sound>());
        auto& metadata {asset.getMetadata<SoundMetadata>()};

        setLooping(metadata.loop);
    }

    void SoundBus::play()
    {
        m_sound.play();
    }

    void SoundBus::pause()
    {
        m_sound.pause();
    }

    void SoundBus::stop()
    {
        m_sound.stop();
    }

    void SoundBus::setVolume(float volume)
    {
        Bus::setVolume(volume);

        m_sound.setVolume(volume * 100.f);
    }

    void SoundBus::setLooping(bool looping)
    {
        m_sound.setLoop(looping);
    }

    bool SoundBus::getLooping() const
    {
        return m_sound.getLoop();
    }

    void SoundBus::setPitch(float pitch)
    {
        m_sound.setPitch(pitch);
    }

    float SoundBus::getPitch() const
    {
        return m_sound.getPitch();
    }
} // tails
