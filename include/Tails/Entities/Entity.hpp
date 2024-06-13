#ifndef TAILS_ENTITY_HPP
#define TAILS_ENTITY_HPP

#include <Tails/Config.hpp>
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

        Entity* read(const nlohmann::json& json) override;

    protected:
        virtual void spawn() {}
        virtual void despawn() {}

        void tick(float deltaTime) override {}
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}
    };
}

#endif // TAILS_ENTITY_HPP
