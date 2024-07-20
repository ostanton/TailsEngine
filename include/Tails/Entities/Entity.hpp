#ifndef TAILS_ENTITY_HPP
#define TAILS_ENTITY_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Transform.hpp>
#include <Tails/JSON/JSONReader.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <nlohmann/json_fwd.hpp>

namespace tails
{
    class LevelState;
    class WorldLayer;

    class TAILS_API Entity :
        public Object,
        public sf::Drawable,
        public sf::Transformable,
        public Tickable,
        public JSONReader
    {
        friend LevelState;

    public:
        void destroy(); // destroys self

        /**
         * If you only want to add to existing Entity loading behaviour, override setEntityDefaults() instead.
         * That method is called here anyway. Override this if you want to overwrite all that functionality.
         * @param json The json object
         * @return Created entity
         */
        Entity* read(const nlohmann::json& json) override;

        /**
         * Checks if this entity is colliding with another entity
         * @param entity The entity we are checking for collision with
         * @return Whether we are colliding
         */
        virtual bool isCollidingWith(Entity* entity) const;

        bool isColliding() {return m_currentCollidingEntity;}

        virtual sf::FloatRect getGlobalBounds() const;

        void setTransform(const Transform& transform);
        Transform makeTransform() const;

        [[nodiscard]] LevelState& getLevel() const;
        [[nodiscard]] WorldLayer& getWorld() const;

    protected:
        virtual void spawn() {}
        virtual void postSpawn() {}
        virtual void despawn() {}

        void tick(float deltaTime) override {}
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}

        /**
         * Sets the default values of this Entity from a json object.
         * Ideally this should be a chain of parent->child->child, etc. of having their members set.
         * @param entity Entity's defaults to set
         * @param json json object to get defaults from
         */
        virtual void setEntityDefaults(Entity* entity, const nlohmann::json& json);

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
