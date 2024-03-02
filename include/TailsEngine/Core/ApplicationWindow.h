#pragma once
#include <memory>
#include <SFML/System/String.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "Obj.h"

namespace tails
{
class AssetCache;
class ResourceManager;
class InputManager;
class Viewport;
class GameInstance;
}

namespace sf
{
class Event;
class VideoMode;
class RenderWindow;
class Clock;
}

namespace tails
{
/**
 * \brief Class that holds the current window and game instance. There is no limit of how many of these can exist,
 * however generally only one should
 */
class ApplicationWindow : public Object
{
    friend Object;
    
public:
    ApplicationWindow();
    
    unique_ptr<sf::VideoMode> videoMode;
    unique_ptr<sf::RenderWindow> renderWindow;
    unique_ptr<sf::Event> windowEvent;
    unique_ptr<sf::Clock> globalClock;
    sf::Time globalTime;
 
    unique_ptr<tails::GameInstance> gameInstance;
    unique_ptr<tails::Viewport> viewport;

    sf::Vector2u windowResolution {960, 640};
    sf::Vector2f viewResolution {240.f, 160.f};
    sf::String windowTitle {"Tails Engine"};
    
    void construct() override;
    
    /**
     * \brief Called after SFML members are initialised. This is where TailsEngine members are initialised.
     */
    virtual void postInitSfml();

    /**
     * \brief Where the default window settings are set. This is called after tails:: classes are initialised,
     * so it is safe to use the resource manager, etc.
     */
    void initWindowSettings();
    
    /**
     * \brief Called once all base members are initialised and ready to use.
     */
    virtual void postInitialise();

    /**
     * \brief Contains the core loop of this window. Calls the game's update method, etc.
     */
    virtual void mainLoop();

    AssetCache& getAssetCache() const;

private:
    unique_ptr<InputManager> m_inputManager;
    unique_ptr<AssetCache> m_assetCache;
};

}