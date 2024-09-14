#ifndef TAILS_ENTITY_HPP
#define TAILS_ENTITY_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Serialisable.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <memory>

namespace tails
{
    class CLevel;
    class CEngine;
    class CResourceManager;
    
    class TAILS_API CEntity :
        public CObject,
        public ITickable,
        public ISerialisable,
        public sf::Drawable,
        public sf::Transformable
    {
        friend CLevel;

    public:
        CEntity();
        ~CEntity() override;
        
        /**
         * Mark this entity for destruction at the start of the next frame.
         */
        void destroy();

        /**
         * Check if this entity is colliding with another.
         * @param entity The entity we're testing collision with
         */
        bool colliding(const CEntity* entity) const;

        sf::FloatRect getGlobalBounds() const;

        void setTexture(sf::Texture* texture);
        [[nodiscard]] sf::Texture* getTexture() const;
        
        void setSize(float x, float y);
        void setSize(const sf::Vector2f& size);
        [[nodiscard]] const sf::Vector2f& getSize() const;

        void setColour(const sf::Color& colour);
        [[nodiscard]] const sf::Color& getColour() const;
        
    protected:
        /**
         * A place to load all the resources that this entity requires/depends on
         * @param resourceManager The resource manager associated with the level this entity is spawned in
         */
        virtual void loadResources(CResourceManager& resourceManager) {}
        
        /**
         * Called the same frame as this entity is spawned.
         */
        virtual void spawn() {}

        /**
         * Called the start of the next frame after this entity is spawned.
         */
        virtual void postSpawn() {}

        /**
         * Called the same frame this entity is despawned/marked for destroy.
         */
        virtual void despawn() {}

        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        /**
         * Called every frame while we are colliding with another entity.
         * @param other The entity we are colliding against
         */
        virtual void collision(CEntity& other) {}

        [[nodiscard]] CLevel& getLevel() const;
        [[nodiscard]] CEngine& getEngine() const;

    private:
        nlohmann::json serialise() const override;
        void deserialise(const nlohmann::json& obj) override;
        std::unique_ptr<ISerialisable> clone() const override;
        
        sf::VertexArray m_vertices {sf::PrimitiveType::TriangleStrip, 4};
        sf::Texture* m_texture {nullptr};
    };
}

#endif // TAILS_ENTITY_HPP
