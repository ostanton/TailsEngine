#include <Tails/Entity.hpp>
#include <Tails/Level.hpp>
#include <Tails/Vector2.hpp>
#include <Tails/Directories.hpp>
#include <Tails/Component.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace tails
{
    CEntity::CEntity() = default;
    CEntity::~CEntity() = default;

    void CEntity::destroy()
    {
        markForDestroy();
        despawn();
    }

    bool CEntity::colliding(const CEntity* entity) const
    {
        if (!entity) return false;

        for (auto& comp : m_components)
        {
            if (comp->getGlobalBounds() == sf::FloatRect())
                continue;

            for (auto& otherComp : entity->m_components)
            {
                if (otherComp->getGlobalBounds() == sf::FloatRect())
                    continue;

                if (comp->getGlobalBounds().findIntersection(otherComp->getGlobalBounds()))
                    return true;
            }
        }

        return false;
    }

    sf::FloatRect CEntity::getGlobalBounds() const
    {
        sf::FloatRect bounds;
        
        for (auto& comp : m_components)
        {
            if (comp->getGlobalBounds().size.x > bounds.size.x)
                bounds.size.x = comp->getGlobalBounds().size.x;
            if (comp->getGlobalBounds().size.y > bounds.size.y)
                bounds.size.y = comp->getGlobalBounds().size.y;
            if (comp->getGlobalBounds().position.x < bounds.position.x)
                bounds.position.x = comp->getGlobalBounds().position.x;
            if (comp->getGlobalBounds().position.y < bounds.position.y)
                bounds.position.y = comp->getGlobalBounds().position.y;
        }
        
        return bounds;
    }

    CComponent* CEntity::createRegisteredComponent(std::string_view className)
    {
        return setupComponent(
            std::unique_ptr<CComponent>(newObject<CComponent>(className, this))
        );
    }

    void CEntity::destroyComponent(CComponent* component)
    {
        if (!component) return;
        
        component->markForDestroy();
        component->destroy();
    }

    void CEntity::initComponents()
    {
        for (const auto& comp : m_components)
        {
            comp->create();
        }
    }

    void CEntity::preTick()
    {
        ITickable::preTick();

        for (const auto& comp : m_components)
        {
            comp->preTick();
            
            if (comp->pendingCreate())
            {
                comp->unmarkForCreate();
                comp->postCreate();
            }
        }
    }

    void CEntity::tick(float deltaTime)
    {
        for (const auto& comp : m_components)
        {
            if (!comp->pendingCreate())
                comp->tick(deltaTime);
        }
    }

    void CEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        
        for (auto& comp : m_components)
        {
            target.draw(*comp, states);
        }
    }

    void CEntity::postTick()
    {
        ITickable::postTick();

        for (auto it = m_components.rbegin(); it != m_components.rend();)
        {
            it->get()->postTick();

            if (it->get()->pendingDestroy())
                it = decltype(it)(m_components.erase(std::next(it).base()));
            else
                ++it;
        }
    }

    CLevel& CEntity::getLevel() const
    {
        return *dynamic_cast<CLevel*>(outer);
    }

    CEngine& CEntity::getEngine() const
    {
        return getLevel().getEngine();
    }

    CComponent* CEntity::setupComponent(std::unique_ptr<CComponent> comp)
    {
        m_components.emplace_back(std::move(comp));
        auto result = m_components.back().get();
        return result;
    }

    void CEntity::serialise(nlohmann::json& obj) const
    {
        obj.push_back({"position"});
        obj["position"].push_back(SVector2f::toJSON(getPosition()));

        obj.push_back({"rotation"});
        obj["rotation"] = getRotation().asDegrees();

        obj.push_back({"scale"});
        obj["scale"].push_back(SVector2f::toJSON(getScale()));
    }
    
    void CEntity::deserialise(const nlohmann::json& obj)
    {
        setPosition(SVector2f::fromJSON(obj["position"]));
        setRotation(sf::degrees(obj["rotation"].get<float>()));
        setScale(SVector2f::fromJSON(obj["scale"]));
    }
}
