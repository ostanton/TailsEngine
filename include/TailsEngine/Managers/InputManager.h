#pragma once
#include <unordered_map>
#include <string>
#include <SFML/Window/Keyboard.hpp>

namespace sf
{
class Event;
}

namespace tails
{
struct Key
{
    bool currentState {false};
    bool previousState {false};
    sf::Keyboard::Key key;
};

/**
 * \brief A class to store simple mappings between keys and actions. Think Unreal Engine's old input system
 * but only the actions (not the axis mappings), and very simple.
 *
 * Since this engine is intended for Game Boy Advance-style games, this really isn't necessary. However it will
 * probably be super useful with generic inputs, like "A" being mapped to sf::Keyboard::X, AND a controller button, etc.
 *
 * This needs to update so it can compare current and previous action states.
 *
 * Base implementation and idea from: https://github.com/WerenskjoldH/SFML-Input-Manager
 */
class InputManager
{
public:
    InputManager();
    
    void preUpdate(sf::Event& e);
    void postUpdate();

    bool isBound(const std::string& action);
    bool isActionDown(const std::string& action);
    bool isActionUp(const std::string& action);
    bool onActionPress(const std::string& action);
    bool onActionRelease(const std::string& action);

    void bindKey(const std::string& action, const sf::Keyboard::Key& key);
    
private:
    std::unordered_map<std::string, std::vector<Key>> m_actionMappings;
};

}
