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
        // tick contexts
        for (auto& value : std::ranges::views::values(m_contexts))
        {
            // loop every action + data in context
            for (auto& mapping : std::ranges::views::values(value.getMappings()))
            {
                bool keyPressed {false};

                // loop the data, seeing if the key associated with it is pressed via its modifiers
                for (const auto& data : mapping.mappingData)
                {
                    if (keyPressed = data.key.isPressed(); keyPressed)
                    {
                        mapping.inputAction.currentValue = true;
                        break;
                    }
                }

                if (keyPressed)
                {
                    mapping.inputAction.execute(ActionTrigger::Triggered);
                }

                if (keyPressed != mapping.inputAction.lastValue.getValue<bool>())
                {
                    if (mapping.inputAction.currentValue.getValue<bool>())
                    {
                        mapping.inputAction.execute(ActionTrigger::Completed);
                        mapping.inputAction.lastValue = mapping.inputAction.currentValue;
                    }
                    else
                    {
                        mapping.inputAction.execute(ActionTrigger::Started);
                        mapping.inputAction.lastValue = mapping.inputAction.currentValue;
                    }
                }
            }
        }
    }
}
