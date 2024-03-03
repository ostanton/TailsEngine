#pragma once
#include <memory>
#include <SFML/System/String.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "Obj.h"

namespace tails
{
class AssetCache;
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

    /**
     * \brief Window's initial resolution. The actual size of the RenderWindow
     */
    sf::Vector2u windowResolution {960, 640};
    /**
     * \brief The internal resolution used by the Views. This is stretched to fit the window size
     */
    sf::Vector2f viewResolution {240.f, 160.f};
    /**
     * \brief The title of the window
     */
    sf::String windowTitle {"Tails Engine"};
    
    void construct() override;
    
    /**
     * \brief Called after SFML members are initialised. This is where TailsEngine members are initialised.
     */
    void postInitSfml();

    /**
     * \brief Where the default window settings are set. This is called after tails:: classes are initialised,
     * so it is safe to use the resource manager, etc.
     */
    void initWindowSettings();
    
    /**
     * \brief Called once all base members are initialised and ready to use.
     */
    void postInitialise();

    /**
     * \brief General function called at the start of each frame to let any objects or data that should be setup
     * be setup. Mainly for dynamically spawning entities and creating widgets. This should not be used for
     * initialisation in any circumstance. The data being setup should already be initialised and valid here
     */
    void setupData();

    /**
     * \brief Contains the core loop of this window. Calls the game's update method, etc.
     */
    void mainLoop();

    /**
     * \brief General function called at the end of each frame to let any objects or data that should be destroyed
     * get destroyed and deleted (mainly for entities in the level)
     */
    void cleanupData();

    AssetCache& getAssetCache() const;

private:
    unique_ptr<InputManager> m_inputManager;
    unique_ptr<AssetCache> m_assetCache;
};

}