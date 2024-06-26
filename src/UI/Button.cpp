#include <Tails/UI/Button.hpp>
#include <Tails/UI/ButtonSlot.hpp>

#include <SFML/Window/Mouse.hpp>

namespace tails
{
    Button::Button()
    {
        m_childMax = 1;
    }

    ButtonSlot* Button::addChildToButton(std::unique_ptr<Widget> content)
    {
        return addChild<ButtonSlot>(std::move(content));
    }

    void Button::tick(float deltaTime)
    {
        PanelWidget::tick(deltaTime);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (!m_pressed)
            {
                pressEvent.broadcast(this);
                m_pressed = true;
            }
        }
    }
} // tails
