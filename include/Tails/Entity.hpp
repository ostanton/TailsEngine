#ifndef TAILS_ENTITY_HPP
#define TAILS_ENTITY_HPP

#include <Tails/Object.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace tails
{
    class Engine;
    class StateStack;
    class LevelState;

    class Entity : public Object, public sf::Drawable, public sf::Transformable
    {
        friend LevelState;

    public:
        void destroy(); // destroys self

    protected:
        virtual void spawn() {}
        virtual void despawn() {}
        virtual void tick(float deltaTime) {}

        LevelState& getLevelState();
        StateStack& getStateStack();
        Engine& getEngine();
    };
}

#endif // TAILS_ENTITY_HPP
