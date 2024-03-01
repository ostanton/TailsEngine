#include "TailsEngine/Managers/InputManager.h"

#include <SFML/Window/Event.hpp>

#include "TailsEngine/Debug/Debug.h"

tails::InputManager::InputManager()
{
    // Default inputs
    
    bindKey("up", sf::Keyboard::Up);
    bindKey("down", sf::Keyboard::Down);
    bindKey("left", sf::Keyboard::Left);
    bindKey("right", sf::Keyboard::Right);

    bindKey("a", sf::Keyboard::X);
    bindKey("b", sf::Keyboard::Z);

    bindKey("start", sf::Keyboard::Enter);
    bindKey("select", sf::Keyboard::Backspace);

    bindKey("l", sf::Keyboard::A);
    bindKey("r", sf::Keyboard::S);
}

void tails::InputManager::preUpdate(sf::Event& e)
{
    if (e.type == sf::Event::KeyReleased)
        for (auto& actionMapping : m_actionMappings)
        {
            auto& keyVector = m_actionMappings.find(actionMapping.first)->second;
            
            for (size_t i {0}; i < keyVector.size(); i++)
            {
                if (keyVector[i].key == e.key.code)
                    keyVector[i].currentState = false;
            }
        }

    if (e.type == sf::Event::KeyPressed)
        for (auto& actionMapping : m_actionMappings)
        {
            auto& keyVector = m_actionMappings.find(actionMapping.first)->second;
            
            for (size_t i {0}; i < keyVector.size(); i++)
            {
                if (keyVector[i].key == e.key.code)
                    keyVector[i].currentState = true;
            }
        }
}

void tails::InputManager::postUpdate()
{
    for (auto& actionMapping : m_actionMappings)
    {
        auto& keyVector = m_actionMappings.find(actionMapping.first)->second;
        
        for (size_t i {0}; i < keyVector.size(); i++)
        {
            keyVector[i].previousState = actionMapping.second[i].currentState;
        }
    }
}

bool tails::InputManager::isBound(const std::string& action)
{
     return m_actionMappings.find(action) != m_actionMappings.end();
}

bool tails::InputManager::isActionDown(const std::string& action)
{
    if (!isBound(action))
        return false;

    // If any of the keys are down
    for (const auto key : m_actionMappings.find(action)->second)
    {
        if (key.currentState)
            return true;
    }

    return false;
}

bool tails::InputManager::isActionUp(const std::string& action)
{
    if (!isBound(action))
        return false;

    // If any of the keys are up
    for (const auto key : m_actionMappings.find(action)->second)
    {
        if (!key.currentState)
            return true;
    }

    return false;
}

bool tails::InputManager::onActionPress(const std::string& action)
{
    if (!isBound(action))
        return false;

    // If any of the keys are now pressed
    for (const auto key : m_actionMappings.find(action)->second)
    {
        if (key.currentState == 1 && key.previousState == 0)
            return true;
    }
    
    return false;
}

bool tails::InputManager::onActionRelease(const std::string& action)
{
    if (!isBound(action))
        return false;

    // If any of the keys are now released
    for (const auto key : m_actionMappings.find(action)->second)
    {
        if (key.currentState == 0 && key.previousState == 1)
            return true;
    }
    
    return false;
}

void tails::InputManager::bindKey(const std::string& action, const sf::Keyboard::Key& key)
{
    Key resultKey;
    resultKey.key = key;

    if (isBound(action))
    {
        auto keyVector = m_actionMappings.find(action)->second;

        bool containsKey {false};
        for (auto iKey : keyVector)
        {
            if (key == iKey.key)
            {
                containsKey = true;
            }
        }

        if (!containsKey)
        {
            Debug::log("Does not contain key, adding to mappings");
            m_actionMappings.find(action)->second.push_back(resultKey);
        }
        else
        {
            Debug::log("Action in mapping already contains this key");
            return;
        }
    }

    // If the action is bound, see if we have this same key bound to it. If not, add it
    /*
    if (isBound(action))
    {
        if (!std::count(keyVector.begin(), keyVector.end(), resultKey))
        {
            m_actionMappings.find(action)->second.push_back(resultKey);
        }
    }*/
    else
    {
        Debug::log("Adding new pair of mappings");
        std::vector<Key> resultKeyVector;
        resultKeyVector.push_back(resultKey);
        m_actionMappings.emplace(std::make_pair(action, resultKeyVector));
    }
}
