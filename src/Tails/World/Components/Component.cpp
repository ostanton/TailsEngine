#include <Tails/World/Components/Component.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/World/Level.hpp>

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
        SMatrix3f worldMatrix {getWorldMatrix()};
        return {worldMatrix.matrix[0][2], worldMatrix.matrix[1][2]};
    }

    SFloatAngle CComponent::getWorldRotation() const noexcept
    {
        return getWorldTransform().getRotation();
    }

    SVector2f CComponent::getWorldScale() const noexcept
    {
        return getWorldTransform().getScale();
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

    SFloatRect CComponent::getWorldBounds() const noexcept
    {
        // TODO - transform the local bounds into world bounds via its world transform/matrix
        //const auto local = getLocalBounds();
        //const auto worldTransform = getWorldTransform();

        const SVector2f worldMin {};
        const SVector2f worldMax {};

        return {
            .position = {maths::min(worldMin.x, worldMax.x), maths::min(worldMin.y, worldMax.y)},
            .size = {maths::min(worldMin.x, worldMax.x), maths::min(worldMin.y, worldMax.y)}
        };
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
