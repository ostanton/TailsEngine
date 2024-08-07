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

        virtual sf::FloatRect getGlobalBounds() const;

        virtual void setTexture(const std::shared_ptr<CTextureAsset>& texture);
        virtual void setSize(float x, float y);
        void setSize(const sf::Vector2f& size);
        
    protected:
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

        [[nodiscard]] CLevel& getLevel() const;
        [[nodiscard]] CEngine& getEngine() const;

    private:
        sf::VertexArray m_vertices {sf::TriangleStrip, 4};
        std::shared_ptr<CTextureAsset> m_texture;
    };
}

#endif // TAILS_ENTITY_HPP
