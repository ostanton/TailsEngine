#pragma once
#include "Obj.h"
#include <SFML/Graphics/Drawable.hpp>

namespace tails
{
class InputManager;
class ResourceManager;
class World;
class ApplicationWindow;
}

namespace sf
{
class Clock;
class View;
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
    
protected:
    /**
     * \brief Called in postInitialise of ApplicationWindow
     */
    void create();
    virtual void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    unique_ptr<sf::View> gameView;
    unique_ptr<sf::Clock> clock;
    unique_ptr<World> world;
};

}
