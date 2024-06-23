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
            // loop every action + data in context
            for (auto& actionMapping : std::ranges::views::values(context.getMappings()))
            {
                if (actionMapping.actionActive())
                {
                    actionMapping.inputAction.currentValue = true;

                    if (actionMapping.inputAction.currentValue != actionMapping.inputAction.lastValue)
                        actionMapping.inputAction.execute(ActionTrigger::Started, true);

                    actionMapping.inputAction.execute(ActionTrigger::Triggered, true);
                }
                else
                {
                    if (actionMapping.inputAction.currentValue != actionMapping.inputAction.lastValue)
                    {
                        actionMapping.inputAction.execute(ActionTrigger::Completed, false);
                    }
                }

                //actionMapping.inputAction.lastValue = actionMapping.inputAction.currentValue;
            }
        }
    }
}
