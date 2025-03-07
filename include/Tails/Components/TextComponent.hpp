#ifndef TAILS_TEXT_COMPONENT_HPP
#define TAILS_TEXT_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Components/TransformComponent.hpp>
#include <Tails/LocaleString.hpp>

#include <SFML/Graphics/Color.hpp>

namespace sf
{
    class Font;
}

namespace tails
{
    class CFont;
    
    /**
     * Localisable text, supporting various stylings and other options
     */
    class TAILS_API CTextComponent : public CTransformComponent
    {
    public:
        /**
         * Style applied to text, all but Normal are meant for bit sets. Normal sets all bits to 0
         */
        enum EStyle
        {
            None = 0,
            Bold = 1 << 0,
            Italic = 1 << 1,
            Underlined = 1 << 2,
            Strikethrough = 1 << 3
        };
        
        CTextComponent() = default;
        CTextComponent(
            CLocaleString string,
            const std::shared_ptr<CFont>& font,
            unsigned int characterSize = 8,
            sf::Color colour = sf::Color::White,
            std::uint8_t style = None,
            float letterSpacing = 1.f,
            float italicShear = 12.f
        );

        void setString(CLocaleString string);
        [[nodiscard]] constexpr const CLocaleString& getString() const {return m_string;}

        void setFont(const std::shared_ptr<CFont>& font);
        [[nodiscard]] std::shared_ptr<CFont> getFont() const;

        void setCharacterSize(unsigned int characterSize);
        [[nodiscard]] constexpr unsigned int getCharacterSize() const {return m_characterSize;}

        void setColour(sf::Color colour);
        [[nodiscard]] constexpr sf::Color getColour() const {return m_colour;}

        void setStyle(std::uint8_t style);
        [[nodiscard]] constexpr bool hasStyle() const {return m_style != None;}
        [[nodiscard]] constexpr bool isBold() const {return m_style & Bold;}
        [[nodiscard]] constexpr bool isItalic() const {return m_style & Italic;}
        [[nodiscard]] constexpr bool isUnderlined() const {return m_style & Underlined;}
        [[nodiscard]] constexpr bool isStrikethrough() const {return m_style & Strikethrough;}

        void setItalicShear(float shear);
        [[nodiscard]] constexpr float getItalicShear() const {return isItalic() ? sf::degrees(m_italicShear).asRadians() : 0.f;}

        void setLetterSpacing(float spacing);
        [[nodiscard]] constexpr float getLetterSpacing() const {return m_letterSpacing;}
        
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        CLocaleString m_string {"Text"};
        std::shared_ptr<CFont> m_font;
        const sf::Font* m_underlying {nullptr};
        unsigned int m_characterSize {8};
        sf::Color m_colour {sf::Color::White};
        std::uint8_t m_style {None};
        float m_letterSpacing {1.f};
        float m_italicShear {12.f};
    };
}
TAILS_REGISTER_CLASS_CUSTOM_NAME(CTextComponent, "TextComponent")

#endif // TAILS_TEXT_COMPONENT_HPP
