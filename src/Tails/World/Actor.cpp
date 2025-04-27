#include <Tails/World/Actor.hpp>
#include <Tails/World/Level.hpp>
#include <Tails/World/Components/ActorComponent.hpp>
#include <Tails/Renderer/Renderer.hpp>

namespace tails
{
    CActor::~CActor() = default;

    CLevel* CActor::getLevel() const
    {
        return m_owningLevel;
    }

    IComponent* CActor::getRootComponent() const
    {
        return m_rootComponent;
    }

    void CActor::setTransform(const STransform2D& transform)
    {
        m_rootComponent->transform = transform;
    }

    const STransform2D& CActor::getTransform() const noexcept
    {
        return m_rootComponent->transform;
    }

    void CActor::setPosition(const SVector2f position)
    {
        m_rootComponent->transform.position = position;
    }

    SVector2f CActor::getPosition() const noexcept
    {
        return m_rootComponent->transform.position;
    }

    void CActor::setRotation(const float rotation)
    {
        m_rootComponent->transform.rotation = rotation;
    }

    float CActor::getRotation() const noexcept
    {
        return m_rootComponent->transform.rotation;
    }

    void CActor::setScale(const SVector2f scale)
    {
        m_rootComponent->transform.scale2D = scale;
    }

    SVector2f CActor::getScale() const noexcept
    {
        return m_rootComponent->transform.scale2D;
    }

    void CActor::setVisible(const bool visible)
    {
        m_rootComponent->visible = visible;
    }

    bool CActor::isVisible() const noexcept
    {
        return m_rootComponent->visible;
    }

    void CActor::destroy() const
    {
        getLevel()->destroyActor(this);
    }

    void CActor::move(const SVector2f offset)
    {
        m_rootComponent->transform.translate(offset);
    }

    bool CActor::isOverlapping(const CActor* other) const noexcept
    {
        if (!other || other == this)
            return false;

        //bool overlapping {false};
        //m_rootComponent->forEachChild([other, &overlapping](CPrimitiveComponent* myComp)
        //{
        //    if (!overlapping)
        //        other->m_rootComponent->forEachChild([myComp, &overlapping](CPrimitiveComponent* otherComp)
        //        {
        //            if (myComp->isOverlapping(otherComp))
        //                overlapping = true;
        //        }, true);
        //}, true);
        //return m_rootComponent->isOverlapping(other->getRootComponent());
        return false;
    }

    void CActor::setLayer(const int layer)
    {
        getLevel()->setActorLayer(this, layer);
    }

    int CActor::getLayer() const noexcept
    {
        return m_layer;
    }

    void CActor::onRender(const CRenderer& renderer) const
    {
        renderer.render(*m_rootComponent);
    }

    void CActor::onInitComponents()
    {
        for (const auto& component : m_components)
        {
            component->onInit();
        }

        // if no root component exists, create one. One should always exist
        if (!m_rootComponent)
        {
            if (m_components.empty())
                createComponent<CActorComponent>();

            m_rootComponent = m_components.front().get();
            m_rootComponent->onInit();
        }
    }

    void CActor::onSpawn()
    {
        
    }

    void CActor::onTick(const float deltaSeconds)
    {
        for (const auto& component : m_components)
        {
            component->onTick(deltaSeconds);
        }
    }

    void CActor::setRootComponent(IComponent* rootComponent)
    {
        if (!rootComponent)
            return;
        
        if (rootComponent->getOwner() != this)
            return;
        
        if (auto const parent = rootComponent->getParent())
        {
            parent->m_children.erase(std::ranges::find(
                parent->m_children.begin(),
                parent->m_children.end(),
                rootComponent
            ));
            rootComponent->setParent(nullptr);
        }

        // TODO - add immediate other components as children of this new root component
        m_rootComponent = rootComponent;
    }

    void CActor::onOverlap(CActor* otherActor)
    {
    }

    IComponent* CActor::addComponent(std::unique_ptr<IComponent> component)
    {
        m_components.emplace_back(std::move(component));
        auto& result = *m_components.back();
        result.m_owner = this;
        return &result;
    }
}
