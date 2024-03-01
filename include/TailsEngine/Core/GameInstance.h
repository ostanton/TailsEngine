#pragma once
#include "Obj.h"
#include <SFML/Graphics/Drawable.hpp>

namespace tails
{
class InputManager;
}

namespace tails
{
class ResourceManager;
}

namespace sf
{
class Clock;
}

namespace tails
{
class World;
class ApplicationWindow;
}

namespace sf
{
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

    ResourceManager& getResourceManager() const;
    InputManager& getInputManager() const;

private:
    unique_ptr<ResourceManager> m_resourceManager;
};

}
