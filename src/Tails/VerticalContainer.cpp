#include <Tails/VerticalContainer.hpp>

namespace tails
{
    void WVerticalContainer::setChildPadding(const SPadding& padding)
    {
        m_childPadding = padding;
    }

    void WVerticalContainer::drawChild(size_t childIndex) const
    {
        CWidget* child {getChildAt(childIndex)};
        CWidget* lastChild {childIndex > 0 ? getChildAt(childIndex - 1) :nullptr};

        if (!lastChild)
        {
            child->setPosition(getPosition());
            return;
        }

        if (!lastChild->getSize().has_value())
        {
            child->setPosition(getPosition());
            return;
        }

        child->setPosition({
            getPosition().x + m_childPadding.left,
            lastChild->getPosition().y + lastChild->getSize().value().y + m_childPadding.top
        });
    }
}
