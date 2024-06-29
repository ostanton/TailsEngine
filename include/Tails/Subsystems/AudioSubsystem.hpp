#ifndef TAILS_AUDIOSUBSYSTEM_HPP
#define TAILS_AUDIOSUBSYSTEM_HPP

#include <Tails/Config.hpp>
#include <Tails/Subsystems/Subsystem.hpp>

#include <vector>
#include <memory>

namespace tails
{
    class Bus;

    class TAILS_API AudioSubsystem final : public Subsystem
    {
    public:
        AudioSubsystem();
        ~AudioSubsystem() override;

        template<typename T>
        size_t createBus()
        {
            static_assert(std::is_base_of_v<Bus, T>, "Failed to create bus, it does not derive Bus");

            return addBus(std::make_unique<T>());
        }

        size_t addBus(std::unique_ptr<Bus> bus);
        Bus* getBus(size_t index);

    protected:
        void init(Engine& engine) override {}
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}

    private:
        std::vector<std::unique_ptr<Bus>> m_buses;
    };
}

#endif // TAILS_AUDIOSUBSYSTEM_HPP
