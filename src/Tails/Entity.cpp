#include <Tails/Entity.hpp>
#include <Tails/Level.hpp>
#include <Tails/TextureAsset.hpp>

#include "SFML/Graphics/RenderTarget.hpp"

namespace tails
{
    CEntity::CEntity()
    {
        setSize(32.f, 32.f);
    }

    void CEntity::destroy()
    {
        markForDestroy();
        onDespawn();
    }

    bool CEntity::colliding(const CEntity* entity) const
    {
        if (!entity) return false;
        
        return getGlobalBounds().intersects(entity->getGlobalBounds());
    }

    sf::FloatRect CEntity::getGlobalBounds() const
    {
        // TODO - TEST
        return getTransform().transformRect(m_vertices.getBounds());
    }

    void CEntity::setTexture(const std::shared_ptr<CTextureAsset>& texture)
    {
        m_texture = texture;

        m_vertices[0].texCoords = {0.f, 0.f};
        m_vertices[1].texCoords = {0.f, static_cast<float>(texture->getSize().y)};
        m_vertices[2].texCoords = {static_cast<float>(texture->getSize().x), 0.f};
        m_vertices[3].texCoords = {
            static_cast<float>(texture->getSize().x),
            static_cast<float>(texture->getSize().y)
        };
    }

    void CEntity::setSize(float x, float y)
    {
        m_vertices[1].position = {0.f, y};
        m_vertices[2].position = {x, 0.f};
        m_vertices[3].position = {x, y};
    }

    void CEntity::setSize(const sf::Vector2f& size)
    {
        setSize(size.x, size.y);
    }

    void CEntity::tick(float deltaTime)
    {
        
    }

    void CEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = m_texture.get();
        target.draw(m_vertices, states);
    }

    CLevel& CEntity::getLevel() const
    {
        return *static_cast<CLevel*>(outer);
    }

    CEngine& CEntity::getEngine() const
    {
        return getLevel().getEngine();
    }

    void CEntity::spawn(CLevel& level)
    {
        outer = &level;
        onSpawn();
    }
}
