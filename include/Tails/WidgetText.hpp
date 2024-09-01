#ifndef TAILS_WIDGETTEXT_HPP
#define TAILS_WIDGETTEXT_HPP

#include <Tails/Config.hpp>
#include <Tails/Widget.hpp>

#include <SFML/System/String.hpp>
#include <SFML/Graphics/Color.hpp>

#include <memory>

namespace sf
{
    class Color;
}

namespace tails
{
    class CFontAsset;

    /**
     * Possibly could switch sf::Text to glyphs and textures.
     */
    class TAILS_API WText final : public CWidget
    {
    public:
        WText() = default;
        WText(const sf::String& text, unsigned int characterSize = 8);
        
        void setText(const sf::String& text);
        [[nodiscard]] const sf::String& getText() const;

        void setFont(std::shared_ptr<CFontAsset> font);
        [[nodiscard]] std::shared_ptr<CFontAsset> getFont() const;

        void setCharacterSize(unsigned int size);
        [[nodiscard]] unsigned int getCharacterSize() const;

        void setFillColour(const sf::Color& colour);
        [[nodiscard]] const sf::Color& getFillColour() const;

        void setOutlineThickness(float thickness);
        [[nodiscard]] float getOutlineThickness() const;

        void setBold(bool bold);
        [[nodiscard]] unsigned int getBold() const;

        void setSize(const sf::Vector2f& size) override;
        std::optional<sf::Vector2f> getSize() const override;

    private:
        void tick(float deltaTime) override {}
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        std::unique_ptr<ISerialisable> clone() const override;

        sf::String m_string {"Text"};
        unsigned int m_characterSize {8};
        float m_outlineThickness {0.f};
        bool m_bold {false};
        sf::Color m_colour {sf::Color::White};
        std::shared_ptr<CFontAsset> m_font;
    };
}

#endif // TAILS_WIDGETTEXT_HPP
