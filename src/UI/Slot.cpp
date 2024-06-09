#include <Tails/UI/Slot.hpp>
#include <Tails/UI/Widget.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    Slot::Slot(PanelWidget* parent, std::unique_ptr<Widget> content)
        : m_parent(parent), m_content(std::move(content))
    {

    }

    Widget* Slot::getContent()
    {
        return m_content.get();
    }

    PanelWidget* Slot::getParent()
    {
        return m_parent;
    }

    void Slot::tick(float deltaTime)
    {
        m_content->tick(deltaTime);
    }

    void Slot::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(*m_content, states);
    }
}
