#include <Tails/Entity.hpp>
#include <Tails/Level.hpp>
#include <Tails/TextureAsset.hpp>
#include <Tails/AssetCache.hpp>
#include <Tails/Vector2.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CEntity::CEntity()
    {
        setSize(16.f, 16.f);
    }

    CEntity::~CEntity() = default;

    void CEntity::destroy()
    {
        markForDestroy();
        despawn();
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

    std::shared_ptr<CTextureAsset> CEntity::getTexture() const
    {
        return m_texture;
    }

    void CEntity::setSize(float x, float y)
    {
        m_vertices[0].position = {0.f, 0.f};
        m_vertices[1].position = {0.f, y};
        m_vertices[2].position = {x, 0.f};
        m_vertices[3].position = {x, y};
    }

    void CEntity::setSize(const sf::Vector2f& size)
    {
        setSize(size.x, size.y);
    }

    const sf::Vector2f& CEntity::getSize() const
    {
        return m_vertices[3].position;
    }

    void CEntity::setColour(sf::Color colour)
    {
        for (size_t i {0}; i < m_vertices.getVertexCount(); i++)
        {
            m_vertices[i].color = colour;
        }
    }

    sf::Color CEntity::getColour() const
    {
        return m_vertices[0].color;
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
        return *dynamic_cast<CLevel*>(outer);
    }

    CEngine& CEntity::getEngine() const
    {
        return getLevel().getEngine();
    }

    nlohmann::json CEntity::serialise() const
    {
        nlohmann::json obj;
        obj.push_back({"position"});
        obj["position"].push_back(TVector2f::toJSON(getPosition()));

        obj.push_back({"rotation"});
        obj["rotation"] = getRotation();

        obj.push_back({"scale"});
        obj["scale"].push_back(TVector2f::toJSON(getScale()));

        obj.push_back({"size"});
        obj["size"].push_back(TVector2f::toJSON(getSize()));
        
        return obj;
    }

    void CEntity::deserialise(const nlohmann::json& obj)
    {
        setPosition(TVector2f::fromJSON(obj["position"]));
        setRotation(obj["rotation"].get<float>());
        setScale(TVector2f::fromJSON(obj["scale"]));
        setSize(TVector2f::fromJSON(obj["size"]));

        // textures
        // TODO - get path of texture ID from whatever engine.ini file or something?
        setTexture(CAssetCache::loadTexture(obj["texture"].get<std::string>(), ""));
    }

    std::unique_ptr<ISerialisable> CEntity::clone() const
    {
        auto obj = std::make_unique<CEntity>();
        obj->setPosition(getPosition());
        obj->setRotation(getRotation());
        obj->setScale(getScale());
        obj->setSize(getSize());
        return obj;
    }

    void CEntity::initSpawn(CLevel* level)
    {
        outer = level;
        spawn();
    }
}
