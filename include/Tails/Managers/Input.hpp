#ifndef TAILS_INPUTMANAGER_HPP
#define TAILS_INPUTMANAGER_HPP

#include <Tails/Managers/Manager.hpp>
#include <Tails/Input/Context.hpp>

#include <unordered_map>
#include <string>

namespace tails
{
    class InputManager final : public Manager
    {
    private:
        void added(EngineSubsystem& engineSubsystem) override;
        void tick(float deltaTime) override;

        std::unordered_map<std::string, InputContext> m_contexts; // use unique_ptr instead?
    };
}

#endif // TAILS_INPUTMANAGER_HPP
