#pragma once
#include <vector>

#include "TailsEngine/Core/Obj.h"

namespace sf
{
class Drawable;
}

namespace tails
{
class Viewport;
}

namespace tails
{
/**
 * \brief Base for all widgets in the UI. Because SFML doesn't virtually inherit in its classes, the diamond
 * problem exists, so we use sf::Drawable for all the members and inputs that should technically have tails::Widget
 * type. This makes it a bit strange to use, but you can cast from the sf::Drawable to get the tails::Widget
 * (or should be able to anyway). TODO - test that!!
 */
class Widget : public Object
{
    friend Viewport;
    
protected:
    virtual void update(float deltaTime);
    
public:
    Widget* parent {nullptr};
    std::vector<unique_ptr<sf::Drawable>> children;

    /**
     * \brief Get the children widgets of this widget as Widget class. Do not alter the result vector, it is a copy.
     * You can alter the Widgets contained within however, as they are pointers
     * \return A copy of the children vector with Widget class pointers
     */
    std::vector<Widget*> getChildrenWidgets() const;

    void addChild(sf::Drawable* child);
};

}
