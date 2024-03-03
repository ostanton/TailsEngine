#pragma once
#include "Screen.h"

namespace sf
{
class RectangleShape;
}

namespace sf
{
class Text;
}

namespace tails
{
/**
 * \brief Test class to test functionality of creation, update, destroy, input, etc.
 */
class TestScreen : public Screen
{
public:
    void display() override;
    void update(float deltaTime) override;

protected:
    sf::Text* m_textWidget {nullptr};
    sf::RectangleShape* m_rectangleShape {nullptr};
};

}
