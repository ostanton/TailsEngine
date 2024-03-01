#include "TailsEngine/Widgets/Widget.h"

#include <SFML/Graphics/Drawable.hpp>

void tails::Widget::update(float deltaTime)
{
    
}

std::vector<tails::Widget*> tails::Widget::getChildrenWidgets() const
{
    std::vector<Widget*> resultVector;

    for (size_t i {0}; i < children.size(); i++)
    {
        resultVector.emplace_back(dynamic_cast<Widget*>(children[i].get()));
    }

    return resultVector;
}

void tails::Widget::addChild(sf::Drawable* child)
{
    children.emplace_back(child);
}
