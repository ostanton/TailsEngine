#ifndef TAILS_ENTITY_HPP
#define TAILS_ENTITY_HPP

#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/JSON/JSONReader.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace tails
{
    class LevelLayer;

    class TAILS_API Entity :
        public Object,
        public sf::Drawable,
        public sf::Transformable,
        public Tickable,
        public JSONReader
    {
        friend LevelLayer;

    public:
        void destroy(); // destroys self

    protected:
        virtual void spawn() {}
        virtual void despawn() {}
    };
}

#endif // TAILS_ENTITY_HPP
