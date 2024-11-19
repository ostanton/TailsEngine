#include <Tails/Entity.hpp>
#include <Tails/Level.hpp>
#include <Tails/Vector2.hpp>
#include <Tails/Directories.hpp>
#include <Tails/Components/Component.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CEntity::CEntity() : m_rootComponent(newObject<CComponent>(this)) {}
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
        auto testCollision = [entity, &colliding](const std::unique_ptr<CComponent>& comp)
        {
            if (comp->getGlobalBounds() == sf::FloatRect())
                return;

            auto testCollision2 = [&comp, &colliding](const std::unique_ptr<CComponent>& comp2)
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

        return colliding;
    }

    sf::FloatRect CEntity::getLocalBounds() const
    {
        sf::FloatRect bounds;

        auto setBounds = [&bounds](const std::unique_ptr<CComponent>& comp)
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
        
        return bounds;
    }

    sf::FloatRect CEntity::getGlobalBounds() const
    {
        return m_rootComponent->getTransform().transformRect(getLocalBounds());
    }
    
    void CEntity::initComponents()
    {
        // root component must always be valid
        if (!m_rootComponent)
            setRootComponent<CComponent>();

        m_rootComponent->create();
        m_rootComponent->forEachChild([](auto& compChild) {compChild->create();}, true);
    }

    void CEntity::preTick()
    {
        ITickable::preTick();
        
        m_rootComponent->preTick();

        if (m_rootComponent->pendingCreate())
            m_rootComponent->unmarkForCreate();
    }

    void CEntity::tick(float deltaTime)
    {
        if (!m_rootComponent->pendingCreate())
            m_rootComponent->tick(deltaTime);
    }

    void CEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (!m_rootComponent->pendingCreate())
            target.draw(*m_rootComponent, states);

        //CDebug::print("Entity left: ", getGlobalBounds().position.x, ", top: ", getGlobalBounds().position.y,
        //    ", right: ", getGlobalBounds().size.x, ", bottom: ", getGlobalBounds().size.y);
    }

    void CEntity::postTick()
    {
        ITickable::postTick();

        m_rootComponent->postTick();

        if (m_rootComponent->pendingDestroy())
        {
            // destroy current root and replace with new, default, root
            m_rootComponent = std::make_unique<CComponent>();
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

    std::vector<CComponent*> CEntity::getComponents() const
    {
        auto result = m_rootComponent->getAllChildren(true);
        result.insert(result.begin(), m_rootComponent.get());
        return result;
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

    CComponent* CEntity::addComponent(std::unique_ptr<CComponent> component) const
    {
        return m_rootComponent->addChild(std::move(component));
    }

    void CEntity::serialise(nlohmann::json& obj) const
    {
        
    }
    
    void CEntity::deserialise(const nlohmann::json& obj)
    {
        
    }
}
