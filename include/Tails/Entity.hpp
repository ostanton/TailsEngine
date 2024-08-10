#ifndef TAILS_ENTITY_HPP
#define TAILS_ENTITY_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <memory>

namespace tails
{
    class CLevel;
    class CEngine;
    class CTextureAsset;
    
    class TAILS_API CEntity :
        public CObject,
        public ITickable,
        public sf::Drawable,
        public sf::Transformable
    {
        friend CLevel;

    public:
        CEntity();
        
        void destroy();
        bool colliding(const CEntity* entity) const;

        virtual sf::FloatRect getGlobalBounds() const;

        virtual void setTexture(const std::shared_ptr<CTextureAsset>& texture);
        virtual void setSize(float x, float y);
        void setSize(const sf::Vector2f& size);
        
    protected:
        /**
         * Called the same frame as this entity is spawned.
         */
        virtual void onSpawn() {}

        /**
         * Called the start of the next frame after this entity is spawned.
         */
        virtual void onPostSpawn() {}

        /**
         * Called the same frame this entity is despawned/marked for destroy.
         */
        virtual void onDespawn() {}

        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        /**
         * Called every frame while we are colliding with another entity.
         * @param other The entity we are colliding against
         */
        virtual void onCollision(CEntity& other) {}

        [[nodiscard]] CLevel& getLevel() const;
        [[nodiscard]] CEngine& getEngine() const;

    private:
        void spawn(CLevel& level);
        
        sf::VertexArray m_vertices {sf::TriangleStrip, 4};
        std::shared_ptr<CTextureAsset> m_texture;
    };
}

#endif // TAILS_ENTITY_HPP
