#ifndef TAILS_AUDIOSUBSYSTEM_HPP
#define TAILS_AUDIOSUBSYSTEM_HPP

#include <Tails/Subsystems/EngineSubsystem.hpp>

namespace tails
{
    class AudioSubsystem : public EngineSubsystem
    {
    protected:
        void init() override {}
        void tick(float deltaTime) override;

    private:
        // vector of Bus class or something? how will audio be managed?
        // vector<Bus> m_buses;
        // int addBus([constructor_params])
        // {
        //     m_buses.emplace_back([constructor_params]);
        // }
        // Bus* getBus(int bus)
        // {
        //     return &m_buses[bus];
        // }
        // void playSound(int bus, const sf::SoundBuffer& buffer)
        // {
        //     m_buses[bus].setBuffer(buffer);
        //     m_buses[bus].play();
        // }
        // max of 8 buses or something. Buses play one buffer each
    };
}

#endif // TAILS_AUDIOSUBSYSTEM_HPP
