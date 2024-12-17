#include <Tails/Entity.hpp>
#include <Tails/Level.hpp>
#include <Tails/Vector2.hpp>
#include <Tails/Components/Component.hpp>
#include <Tails/Components/TransformComponent.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

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

        bool colliding {false};
        /*
        auto testCollision = [entity, &colliding](const std::unique_ptr<CTransformComponent>& comp)
        {
            if (comp->getGlobalBounds() == sf::FloatRect())
                return;

            auto testCollision2 = [&comp, &colliding](const std::unique_ptr<CTransformComponent>& comp2)
            {
                if (comp2->getGlobalBounds() == sf::FloatRect())
                    return;

                if (comp->getGlobalBounds().findIntersection(comp2->getGlobalBounds()))
                    colliding = true;
            };

            testCollision2(entity->m_rootComponent);
            entity->m_rootComponent->forEachChild(testCollision2, true);
        };

        testCollision(m_rootComponent);
        m_rootComponent->forEachChild(testCollision, true);
        */
        return colliding;
    }

    sf::FloatRect CEntity::getLocalBounds() const
    {
        sf::FloatRect bounds;

        /*
        auto setBounds = [&bounds](const std::unique_ptr<CTransformComponent>& comp)
        {
            if (comp->getGlobalBounds().size.x > bounds.size.x)
                bounds.size.x = comp->getGlobalBounds().size.x;
            if (comp->getGlobalBounds().size.y > bounds.size.y)
                bounds.size.y = comp->getGlobalBounds().size.y;
            if (comp->getGlobalBounds().position.x < bounds.position.x)
                bounds.position.x = comp->getGlobalBounds().position.x;
            if (comp->getGlobalBounds().position.y < bounds.position.y)
                bounds.position.y = comp->getGlobalBounds().position.y;
        };

        setBounds(m_rootComponent);
        m_rootComponent->forEachChild(setBounds, true);

        bounds = m_rootComponent->getTransform().transformRect(bounds);
        */
        return bounds;
    }

    sf::FloatRect CEntity::getGlobalBounds() const
    {
        return m_rootComponent->getTransform().transformRect(getLocalBounds());
    }

    CComponent* CEntity::createRegisteredComponent(const std::string_view name)
    {
        return createRegisteredComponent<CComponent>(name);
    }

    void CEntity::initComponents()
    {
        // root component must always be valid
        if (!m_rootComponent)
            setRootComponent(createComponent<CTransformComponent>());

        for (const auto& component : m_components)
        {
            component->create();
            component->unmarkForCreate();
        }
    }

    void CEntity::preTick()
    {
        ITickable::preTick();
        
        for (const auto& component : m_components)
        {
            component->preTick();

            if (component->pendingCreate())
            {
                component->create();
                component->unmarkForCreate();
            }
        }
    }

    void CEntity::tick(const float deltaTime)
    {
        //CDebug::print("Component count: ", m_components.size());
        for (const auto& component : m_components)
        {
            if (!component->pendingCreate())
                component->tick(deltaTime);
        }
    }

    void CEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (const auto& component : m_components)
        {
            if (component->pendingCreate())
            {
                continue;
            }

            if (auto const drawable = dynamic_cast<CTransformComponent*>(component.get()))
            {
                /* TODO - does not work with child components, e.g.:
                 * Sprite (root)
                 *   Sprite (works)
                 *     Sprite (offset by parent's transform, bad!)
                 */
                if (auto const parent = drawable->getParent())
                    states.transform *= parent->getTransform();

                target.draw(*drawable, states);
            }
        }

        //CDebug::print("Entity left: ", getGlobalBounds().position.x, ", top: ", getGlobalBounds().position.y,
        //    ", right: ", getGlobalBounds().size.x, ", bottom: ", getGlobalBounds().size.y);
    }

    void CEntity::postTick()
    {
        ITickable::postTick();

        for (auto it = m_components.rbegin(); it != m_components.rend();)
        {
            (*it)->postTick();

            if ((*it)->pendingDestroy())
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

    void CEntity::setPosition(const sf::Vector2f& position) const
    {
        m_rootComponent->setPosition(position);
    }

    void CEntity::setRotation(const sf::Angle& angle) const
    {
        m_rootComponent->setRotation(angle);
    }

    void CEntity::setScale(const sf::Vector2f& scale) const
    {
        m_rootComponent->setScale(scale);
    }

    void CEntity::move(const sf::Vector2f& offset) const
    {
        m_rootComponent->move(offset);
    }

    sf::Vector2f CEntity::getPosition() const
    {
        return m_rootComponent->getPosition();
    }

    sf::Angle CEntity::getRotation() const
    {
        return m_rootComponent->getRotation();
    }

    sf::Vector2f CEntity::getScale() const
    {
        return m_rootComponent->getScale();
    }

    const sf::Transform& CEntity::getTransform() const
    {
        return m_rootComponent->getTransform();
    }

    const sf::Transform& CEntity::getInverseTransform() const
    {
        return m_rootComponent->getInverseTransform();
    }

    void CEntity::setRootComponent(CTransformComponent* component)
    {
        m_rootComponent = component;
    }

    CComponent* CEntity::addComponent(std::unique_ptr<CComponent> component)
    {
        m_components.emplace_back(std::move(component));
        return m_components.back().get();
    }

    void CEntity::serialise(nlohmann::json& obj) const
    {
        
    }
    
    void CEntity::deserialise(const nlohmann::json& obj)
    {
        
    }
}
