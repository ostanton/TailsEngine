#include <Tails/Subsystems/InputSubsystem.hpp>

#include <ranges>

namespace tails
{
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
                // is this current action pressed
                bool actionPressed {false};

                // loop the data, seeing if the key associated with it is pressed via its modifiers
                for (auto& data : mapping.mappingData)
                {
                    if (data.key.isPressed())
                    {
                        actionPressed = true;
                        break;
                    }
                }

                if (actionPressed)
                {
                    mapping.inputAction.execute(ActionTrigger::Triggered, InputValue(true));
                }
            }
        }
    }
}
