#pragma once
#include <memory>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "InputTypes.h"
#include "Obj.h"
#include "TailsEngine/Managers/InputManager.h"
#include "TailsEngine/Managers/Assets/AssetCache.h"

namespace sf
{
class Sprite;
}

namespace sf
{
class RenderTexture;
}

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
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;
    sf::Event windowEvent;
    sf::Clock globalClock;
    sf::Time globalTime;
    sf::View windowView;
 
    unique_ptr<GameInstance> gameInstance;
    unique_ptr<Viewport> viewport;

    /**
     * \brief Current input mode to dictate where input should be routed
     */
    InputMode inputMode {InputMode::GameAndViewport};

    /**
     * \brief Window's initial resolution. The actual size of the RenderWindow
     */
    sf::Vector2u windowResolution {960, 640};
    /**
     * \brief The internal resolution used by the Views. This is stretched to fit the window size
     */
    sf::Vector2u viewResolution {240, 160};
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
    void setupData() override;

    /**
     * \brief Contains the core loop of this window. Calls the game's update method, etc.
     */
    void mainLoop();

    /**
     * \brief General function called at the end of each frame to let any objects or data that should be destroyed
     * get destroyed and deleted (mainly for entities in the level)
     */
    void cleanupData() override;

private:
    InputManager m_inputManager;
    AssetCache m_assetCache;

    /**
     * \brief Calculate the internal viewport size to match its intended aspect ratio
     * \param width Window width
     * \param height Window height
     */
    void calculateAspectRatio(unsigned width, unsigned height);
    /**
     * \brief Calculate the internal viewport size to match its intended aspect ratio
     * \param size Window size
     */
    void calculateAspectRatio(const sf::Vector2u& size);
};

}
