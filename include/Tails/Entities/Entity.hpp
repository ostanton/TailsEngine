#ifndef TAILS_ENTITY_HPP
#define TAILS_ENTITY_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/JSON/JSONReader.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <nlohmann/json_fwd.hpp>

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

        /**
         * Checks if this entity is colliding with another entity
         * @param entity The entity we are checking for collision with
         * @return Whether we are colliding
         */
        virtual bool isCollidingWith(Entity* entity);

        bool isColliding() {return m_currentCollidingEntity;}

        virtual sf::FloatRect getGlobalBounds() const;

    protected:
        virtual void spawn() {}
        virtual void despawn() {}

        void tick(float deltaTime) override {}
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}

        // TODO - derived classes override this and provide their own defaults? Or make a new method of their own?
        void setEntityDefaults(Entity* entity, const nlohmann::json& json);

        /**
         * Called when a collision between this entity and another starts
         * @param other The entity we are colliding with
         */
        virtual void collisionStart(Entity* other) {}
        /**
         * Called when a collision between this entity and another ends
         * @param other The entity we just stopped colliding with
         */
        virtual void collisionEnd(Entity* other) {}

    private:
        Entity* m_currentCollidingEntity {nullptr};
        Entity* m_lastCollidingEntity {nullptr};
    };
}

#endif // TAILS_ENTITY_HPP
