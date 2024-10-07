#include <Tails/TextComponent.hpp>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace tails
{
    CTextComponent::CTextComponent(
        CLocaleString string,
        const sf::Font* font,
        unsigned int characterSize,
        sf::Color colour,
        std::uint8_t style,
        float letterSpacing,
        float italicShear
    ) :
        m_string(std::move(string)),
        m_font(font),
        m_characterSize(characterSize),
        m_colour(colour),
        m_style(style),
        m_letterSpacing(letterSpacing),
        m_italicShear(italicShear)
    {
    }

    void CTextComponent::setString(CLocaleString string)
    {
        m_string = std::move(string);
    }

    void CTextComponent::setFont(const sf::Font* font)
    {
        m_font = font;
    }

    void CTextComponent::setColour(sf::Color colour)
    {
        m_colour = colour;
    }

    void CTextComponent::setCharacterSize(unsigned int characterSize)
    {
        m_characterSize = characterSize;
    }

    void CTextComponent::setStyle(std::uint8_t style)
    {
        m_style = style;
    }

    void CTextComponent::setItalicShear(float shear)
    {
        m_italicShear = shear;
    }

    void CTextComponent::setLetterSpacing(float spacing)
    {
        m_letterSpacing = spacing;
    }

    void CTextComponent::tick(float deltaTime)
    {
        
    }

    void CTextComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (!m_font || m_string.isEmpty()) return;

        states.transform *= getTransform();
        states.texture = &m_font->getTexture(m_characterSize);
        states.coordinateType = sf::CoordinateType::Pixels;

        sf::VertexArray vertices {sf::PrimitiveType::TriangleStrip, m_string.getSize()};
        
        for (const auto strChar : m_string)
        {
            auto& glyph = m_font->getGlyph(strChar, m_characterSize, isBold());
            // TODO - add glyph to vertex array!
        }

        target.draw(vertices, states);
    }
}
