#ifndef TAILS_INPUTSUBSYSTEM_HPP
#define TAILS_INPUTSUBSYSTEM_HPP

#include <Tails/Subsystems/Subsystem.hpp>
#include <Tails/Input/Context.hpp>

#include <unordered_map>
#include <string>

namespace tails
{
    class TAILS_API InputSubsystem final : public Subsystem
    {
    private:
        void init(Engine& engine) override;
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}

        std::unordered_map<std::string, InputContext> m_contexts; // use unique_ptr instead?
    };
}

#endif // TAILS_INPUTSUBSYSTEM_HPP
