#include <Tails/Game/Components/PrimitiveComponent.hpp>

namespace tails
{
    void CPrimitiveComponent::setParent(CPrimitiveComponent* parent)
    {
        // TODO - might want to detach ourselves from our last parent if new parent == nullptr?
        m_parent = parent;

        if (!parent)
            return;

        parent->addChild(this);
    }

    CPrimitiveComponent* CPrimitiveComponent::getParent() const
    {
        return m_parent;
    }

    SFloatRect CPrimitiveComponent::getGlobalBounds() const noexcept
    {
        return {};
    }

    bool CPrimitiveComponent::isOverlapping(const CPrimitiveComponent* other) const noexcept
    {
        // don't overlap self
        // TODO - don't overlap siblings or children either!
        if (!other || other == this)
            return false;

        return getGlobalBounds().intersects(other->getGlobalBounds());
    }

    void CPrimitiveComponent::onRender(IRenderer& renderer) const
    {
    }

    void CPrimitiveComponent::onOverlap(CPrimitiveComponent* otherComponent)
    {
    }

    void CPrimitiveComponent::addChild(CPrimitiveComponent* child)
    {
        if (!m_firstChild)
        {
            m_firstChild = child;
            return;
        }

        for (auto nextChild {m_firstChild}; nextChild; nextChild = nextChild->m_nextSibling)
        {
            if (!nextChild->m_nextSibling)
            {
                nextChild->m_nextSibling = child;
                break;
            }
        }
    }

    CPrimitiveComponent* CPrimitiveComponent::getLastChild() const
    {
        CPrimitiveComponent* nextChild {m_firstChild};
        while (nextChild)
        {
            nextChild = nextChild->m_nextSibling;
        }
        return nextChild;
    }
}
