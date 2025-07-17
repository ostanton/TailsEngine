#include <Tails/World/Components/Component.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/World/Level.hpp>
#include <Tails/Maths/SAT.hpp>

#include <algorithm>

namespace tails
{
    CActor* CComponent::getOwner() const noexcept
    {
        return m_owner;
    }

    CLevel* CComponent::getLevel() const noexcept
    {
        if (!m_owner)
            return nullptr;

        return m_owner->getLevel();
    }

    void CComponent::setParent(CComponent* parent) noexcept
    {
        // components cannot be parents of themselves
        if (parent == this)
            return;

        // remove from old parent
        if (m_parent)
        {
            m_parent->m_children.erase(std::ranges::find(
                m_parent->m_children.begin(),
                m_parent->m_children.end(),
                this
            ));
        }

        // add to new parent
        m_parent = parent;

        if (m_parent)
            m_parent->m_children.push_back(this);
    }

    CComponent* CComponent::getParent() const noexcept
    {
        return m_parent;
    }

    SVector2f CComponent::getWorldPosition() const noexcept
    {
        return getWorldMatrix().getTranslation();
    }

    SFloatAngle CComponent::getWorldRotation() const noexcept
    {
        return getWorldMatrix().getRotation();
    }

    SVector2f CComponent::getWorldScale() const noexcept
    {
        return getWorldMatrix().getScale();
    }

    STransform2D CComponent::getWorldTransform() const noexcept
    {
        if (m_parent)
            return {m_parent->getWorldMatrix() * transform.getMatrix()};

        return transform;
    }

    SMatrix3f CComponent::getWorldMatrix() const noexcept
    {
        if (m_parent)
            return m_parent->getWorldMatrix() * transform.getMatrix();

        return transform.getMatrix();
    }

    void CComponent::onRender(CLevelRenderBatch& renderBatch) const
    {
        for (auto const child : m_children)
        {
            child->onRender(renderBatch);
        }
    }

    SFloatRect CComponent::getLocalBounds() const noexcept
    {
        return {};
    }

    SFloatOrientedRect CComponent::getWorldBounds() const noexcept
    {
        return getWorldMatrix().transformToOrientedRect(getLocalBounds());
    }

    SSATShape CComponent::getSATShape() const noexcept
    {
        const auto corners = getWorldBounds().getCorners();
        return {{corners[0], corners[1], corners[2], corners[3]}};
    }

    bool CComponent::isCollidingWith(const CComponent* other) const noexcept
    {
        if (auto const level = getLevel())
            return level->areColliding(this, other);

        return false;
    }

    std::vector<CComponent*> CComponent::getCollidingComponents() const noexcept
    {
        if (auto const level = getLevel())
            return level->getCollisionsFor(this);

        return {};
    }

    void CComponent::onInit()
    {
    }

    void CComponent::onTick(float deltaSeconds)
    {
    }

    void CComponent::onDeinit()
    {
    }

    void CComponent::onStartCollision(CComponent* otherComponent)
    {
    }

    void CComponent::onCollision(CComponent* otherComponent)
    {
    }

    void CComponent::onEndCollision(CComponent* otherComponent)
    {
    }

    void CComponent::addChild(CComponent* child) noexcept
    {
        if (!child)
            return;

        // remove from its current parent
        if (auto const parent = child->getParent())
        {
            parent->m_children.erase(std::ranges::find(
                parent->m_children.begin(),
                parent->m_children.end(),
                child
            ));
        }

        // setup this new parent relationship
        child->m_parent = this;
        m_children.push_back(child);
    }
}
