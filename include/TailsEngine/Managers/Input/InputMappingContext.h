#pragma once
#include <memory>
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>

namespace tails
{
class InputActionModifier;
class InputAction;
}

namespace tails
{
/**
 * \brief Holds the key itself and whatever modifiers affect the output
 */
struct InputKeyBinding final
{
    sf::Keyboard::Key key;
    std::vector<std::unique_ptr<InputActionModifier>> modifiers;

    template<typename ModifierT>
    void addModifier()
    {
        static_assert(std::is_base_of_v<InputActionModifier, ModifierT>, "Cannot add non-modifier class to key binding");
        modifiers.emplace_back(std::make_unique<ModifierT>());
    }
};

/**
 * \brief Where all the bindings between the keys and actions are stored and set up. Subclass to create your own.
 * Very much inspired by Unreal Engine's Enhanced Input System. The idea here is to create a subclass of InputAction
 * and InputMappingContext, and add that InputAction class to the context. You can then add InputKeyBinding objects
 * to a binding to change how it should behave.
 * 
 * The InputManager then checks the current InputMappingContext, and decides if an action is pressed or not, like
 * how it does at the moment before this new system. Checking for if a certain action is pressed would be cumbersome,
 * so some delegate/binding to methods would need to be in effect, but that is super complicated, so is on the
 * back-burner for now. The current system works great either way. This is just here to expand if needed as a
 * proof-of-concept
 */
class InputMappingContext
{
public:
    virtual ~InputMappingContext() = default;
    
    template<typename ActionT>
    void addActionMapping(const std::vector<InputKeyBinding>& bindings)
    {
        static_assert(std::is_base_of_v<InputAction, ActionT>, "Cannot add non-action class to action mapping");
        m_mappings.emplace(std::make_unique<ActionT>(), bindings);
    }

private:
    std::unordered_map<std::unique_ptr<InputAction>, std::vector<InputKeyBinding>> m_mappings;
};

}
