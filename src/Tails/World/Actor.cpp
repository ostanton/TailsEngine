#include <Tails/World/Actor.hpp>
#include <Tails/World/Level.hpp>
#include <Tails/World/Components/Component.hpp>

#include <ranges>

namespace tails
{
    CActor::~CActor() = default;

    CLevel* CActor::getLevel() const
    {
        if (m_owningLevel.expired())
            return nullptr;

        return m_owningLevel.lock().get();
    }

    std::weak_ptr<CLevel> CActor::getLevelWeak() const
    {
        return m_owningLevel;
    }

    CComponent* CActor::getRootComponent() const
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
        m_rootComponent->transform.setPosition(position);
    }

    SVector2f CActor::getPosition() const noexcept
    {
        return m_rootComponent->transform.getPosition();
    }

    void CActor::setRotation(const SFloatAngle rotation)
    {
        m_rootComponent->transform.setRotation(rotation);
    }

    SFloatAngle CActor::getRotation() const noexcept
    {
        return m_rootComponent->transform.getRotation();
    }

    void CActor::setScale(const SVector2f scale)
    {
        m_rootComponent->transform.setScale(scale);
    }

    SVector2f CActor::getScale() const noexcept
    {
        return m_rootComponent->transform.getScale();
    }

    void CActor::setVisible(const bool visible)
    {
        if (visible)
            flags.setBit(IsVisible);
        else
            flags.clearBit(IsVisible);
    }

    bool CActor::isVisible() const noexcept
    {
        return flags.isBitSet(IsVisible);
    }

    void CActor::destroy()
    {
        // End of this frame the level will cleanup all pending kill actors
        flags.setBit(PendingKill);
        onDespawn();
    }

    void CActor::move(const SVector2f offset)
    {
        m_rootComponent->transform.translate(offset);
    }

    void CActor::setLayer(const int layer)
    {
        if (!getLevelWeak().expired())
            getLevelWeak().lock()->setActorLayer(this, layer);
    }

    int CActor::getLayer() const noexcept
    {
        return m_layer;
    }

    void CActor::onRender(CLevelRenderBatch& renderBatch) const
    {
        if (!flags.isBitSet(IsVisible))
            return;

        m_rootComponent->onRender(renderBatch);
    }

    bool CActor::isCollidingWith(const CActor* other) const noexcept
    {
        if (!other)
            return false;

        for (const auto& myComp : m_components)
        {
            for (const auto& otherComp : other->m_components)
            {
                if (myComp->getWorldBounds().intersects(otherComp->getWorldBounds()))
                    return true;
            }
        }

        return false;
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
                createComponent<CComponent>();

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

    void CActor::onDespawn()
    {
        // deinit components
        for (const auto& component : m_components)
        {
            component->onDeinit();
        }
    }

    void CActor::setRootComponent(CComponent* rootComponent)
    {
        if (!rootComponent)
            return;

        if (rootComponent->getOwner() != this)
            return;

        rootComponent->setParent(nullptr);

        // TODO - add immediate other components as children of this new root component
        m_rootComponent = rootComponent;
    }

    void CActor::onOverlap(CActor* otherActor)
    {
    }

    CComponent* CActor::addComponent(std::unique_ptr<CComponent> component)
    {
        m_components.emplace_back(std::move(component));
        auto& result = *m_components.back();
        result.m_owner = this;
        return &result;
    }
}
