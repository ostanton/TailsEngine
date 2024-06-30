#include <Tails/Subsystems/InputSubsystem.hpp>

#include <ranges>

namespace tails
{
    void InputSubsystem::addContext(const std::string& name, InputContext& context)
    {
        m_contexts.try_emplace(name, std::move(context));
    }

    void InputSubsystem::init(Engine& engine)
    {
        // load inputs from json via engine's paths variables
    }

    void InputSubsystem::tick(float deltaTime)
    {
        // loop contexts
        for (auto& context : std::ranges::views::values(m_contexts))
        {
            context.tick(deltaTime);
        }
    }
}
