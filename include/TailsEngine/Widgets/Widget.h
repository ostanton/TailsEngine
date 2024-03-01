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
 * \brief There are two ways I can see of making these widgets. Either have this as a kind of abstract virtual class
 * for "helping" with whatever its derived classes do (where its derived classes inherit from tails::Widgets and
 * sf::Text or sf::Sprite, etc.). OR, have this class and its derived classes act as wrapper classes for the SFML
 * classes. This would mean the tails::Widget class needs to inherit sf::Drawable and sf::Transformable, and very
 * possible override some methods to wrap their member's positions and rotations, etc., which takes time, and I don't
 * think sf::Transformable's methods are even virtual, so I'd need to make my own.
 *
 * So, in interest of keeping the engine simple, I will have a vector of sf::Drawable, which I can then cast to
 * their desired SFML-inherited types. To cast to this tails::Widget type would then require an up-cast from that
 * custom type (e.g. tails::TextWidget : sf::Text, tails::Widget). This will probably get refactored a bit over time,
 * so nothing is concrete or done yet.
 *
 * This class is unused currently
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
