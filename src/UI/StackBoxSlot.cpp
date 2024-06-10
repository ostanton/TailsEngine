#include <Tails/UI/StackBoxSlot.hpp>
#include <Tails/UI/StackBox.hpp>

namespace tails
{
    StackBoxSlot::StackBoxSlot(PanelWidget* parent, std::unique_ptr<Widget> content)
        : PanelSlot(parent, std::move(content))
    {

    }

    StackBox* StackBoxSlot::getParentStackBox()
    {
        return static_cast<StackBox*>(getParent());
    }

    void StackBoxSlot::tick(float deltaTime)
    {
        Slot::tick(deltaTime);

        size_t childCount = getParentStackBox()->getChildrenCount();
        sf::Vector2f stackSize = getParentStackBox()->getSize();
        sf::Vector2f stackPos = getParentStackBox()->getPosition();
        // BUG - if we are index 0 or 1, subtracting 1 could be bad, so check for that?
        size_t childrenBefore = getParentStackBox()->getChildIndex(getContent()) - 1;

        sf::Vector2f contentSize = stackSize / static_cast<float>(childCount);
        sf::Vector2f contentOffset = stackPos + (static_cast<float>(childrenBefore) * contentSize);

        switch (getParentStackBox()->orientation)
        {
            case Orientation::Horizontal:
                getContent()->setSize(contentSize.x, stackSize.y);
                getContent()->setPosition(contentOffset.x, stackPos.y);
                break;
            case Orientation::Vertical:
                getContent()->setSize(stackSize.x, contentSize.y);
                getContent()->setPosition(stackPos.x, contentOffset.y);
                break;
        }
    }
}
