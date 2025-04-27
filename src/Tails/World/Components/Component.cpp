#include <Tails/World/Components/Component.hpp>
#include <Tails/Renderer/Renderer.hpp>

#include <algorithm>

namespace tails
{
    CActor* IComponent::getOwner() const noexcept
    {
        return m_owner;
    }

    void IComponent::setParent(IComponent* parent) noexcept
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

    IComponent* IComponent::getParent() const noexcept
    {
        return m_parent;
    }

    void IComponent::onRender(const CRenderer& renderer) const
    {
        for (auto const child : m_children)
        {
            renderer.render(*child);
        }
    }

    void IComponent::onInit()
    {
    }

    void IComponent::addChild(IComponent* child) noexcept
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
