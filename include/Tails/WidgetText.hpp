#ifndef TAILS_WIDGETTEXT_HPP
#define TAILS_WIDGETTEXT_HPP

#include <Tails/Config.hpp>
#include <Tails/Widget.hpp>

#include <SFML/Graphics/Text.hpp>

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
    class TAILS_API WText : public CWidget
    {
    public:
        WText();
        
        void setText(const sf::String& text);
        [[nodiscard]] const sf::String& getText() const;

        void setFont(std::shared_ptr<CFontAsset> font);
        [[nodiscard]] std::shared_ptr<CFontAsset> getFont() const;

        void setCharacterSize(unsigned int size);
        [[nodiscard]] unsigned int getCharacterSize() const;

        void setLineSpacing(float factor);
        [[nodiscard]] float getLineSpacing() const;

        void setLetterSpacing(float factor);
        [[nodiscard]] float getLetterSpacing() const;

        void setFillColour(const sf::Color& colour);
        [[nodiscard]] const sf::Color& getFillColour() const;

        void setOutlineColour(const sf::Color& colour);
        [[nodiscard]] const sf::Color& getOutlineColour() const;

        void setOutlineThickness(float thickness);
        [[nodiscard]] float getOutlineThickness() const;

        void setStyle(sf::Text::Style style);
        [[nodiscard]] unsigned int getStyle() const;

    protected:
        void tick(float deltaTime) override {}
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Text m_text;
        std::shared_ptr<CFontAsset> m_font;
    };
}

#endif // TAILS_WIDGETTEXT_HPP
