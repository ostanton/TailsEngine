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
        if (!parent)
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
        m_parent->m_children.push_back(this);
    }

    CComponent* CComponent::getParent() const noexcept
    {
        return m_parent;
    }

    STransform2D CComponent::getScreenSpaceTransform() const noexcept
    {
        if (auto const level = getLevel())
            return level->worldToScreen(transform);

        return {};
    }

    void CComponent::onRender(CLevelRenderBatch& renderBatch) const
    {
        for (auto const child : m_children)
        {
            child->onRender(renderBatch);
        }
    }

    void CComponent::onInit()
    {
    }

    void CComponent::onTick(float deltaSeconds)
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
