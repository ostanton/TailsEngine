#pragma once
#include "Obj.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

namespace tails
{
class Viewport;
class InputManager;
class World;
class ApplicationWindow;
}

namespace sf
{
class Event;
}

namespace tails
{
/**
 * \brief The current "game" itself. This holds references to the world, the game's sf::View class, etc.
 */
class GameInstance : public Object, public sf::Drawable
{
    friend ApplicationWindow;
    
public:
    GameInstance();

    void construct() override;

    void pauseGame(bool pause);
    bool isGamePaused() const;

    Viewport& getViewport() const;
    
protected:
    /**
     * \brief Called in postInitialise of ApplicationWindow
     */
    void create();
    virtual void processInput(sf::Event& e);
    virtual void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool m_gamePaused {false};

    void setupData() override;
    void cleanupData() override;

public:
    sf::View gameView;
    sf::Clock clock;
    unique_ptr<World> world;
};

}
