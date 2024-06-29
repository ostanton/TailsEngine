#ifndef TAILS_AUDIOBUS_HPP
#define TAILS_AUDIOBUS_HPP

#include <Tails/Config.hpp>

namespace tails
{
    struct AssetInfo;

    /**
     * An abstraction of what sound is. It can influence sound in whatever way it wants, and allows you to freely
     * do things without worrying about how those things are implemented
     */
    class TAILS_API Bus
    {
    public:
        virtual ~Bus() = default;

        virtual void setAsset(const AssetInfo& asset) = 0;

        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;

        /**
         * Set volume between 0 and 1
         * @param volume Volume of the bus
         */
        virtual void setVolume(float volume) {m_volume = volume;}
        virtual void setPanning(float) {}
        virtual void setLooping(bool) {}
        virtual void setPitch(float) {}

        /**
         * Get volume between 0 and 1
         * @return Volume of the bus
         */
        [[nodiscard]] virtual float getVolume() const {return m_volume;}
        [[nodiscard]] virtual float getPanning() const {return 0.f;}
        [[nodiscard]] virtual bool getLooping() const {return false;}
        [[nodiscard]] virtual float getPitch() const {return 1.f;}

        // effects, etc.

    protected:
        // normalised volume
        float m_volume {0.f};
    };
} // tails

#endif //TAILS_AUDIOBUS_HPP
