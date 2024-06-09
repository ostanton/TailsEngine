#ifndef TAILS_WIDGETSLOT_HPP
#define TAILS_WIDGETSLOT_HPP

#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>

#include <memory>

namespace tails
{
    class Widget;
    class PanelWidget;

    class Slot : public Object, public sf::Drawable, public Tickable
    {
    public:
        Slot() = default;
        Slot(PanelWidget* parent, std::unique_ptr<Widget> content);

        Widget* getContent();
        PanelWidget* getParent();

    protected:
        PanelWidget* m_parent {nullptr};
        std::unique_ptr<Widget> m_content;

        void tick(float deltaTime) override;
        // TODO - specialised "layout" method that takes a PanelWidget as input?
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif // TAILS_WIDGETSLOT_HPP
