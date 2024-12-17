#include <Tails/Components/TextComponent.hpp>

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

    sf::FloatRect CTextComponent::getGlobalBounds() const
    {
        return CTransformComponent::getGlobalBounds();
    }

    void CTextComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        CTransformComponent::draw(target, states);
        
        if (!m_font || m_string.isEmpty()) return;

        states.transform *= getTransform();
        states.texture = &m_font->getTexture(m_characterSize);
        states.coordinateType = sf::CoordinateType::Pixels;

        // TODO - optimise or something idk
        sf::VertexArray vertices {sf::PrimitiveType::TriangleStrip};
        float x {0.f};
        float y {0.f};
        
        for (const auto strChar : m_string)
        {
            auto& glyph = m_font->getGlyph(strChar, m_characterSize, isBold());
            // TODO - support multi-line, etc.
            
            float left {glyph.bounds.position.x};
            float top {glyph.bounds.position.y};
            float right {left + glyph.bounds.size.x};
            float bottom {top + glyph.bounds.size.y};
            
            float u1 {static_cast<float>(glyph.textureRect.position.x)};
            float v1 {static_cast<float>(glyph.textureRect.position.y)};
            float u2 {u1 + static_cast<float>(glyph.textureRect.size.x)};
            float v2 {v1 + static_cast<float>(glyph.textureRect.size.y)};

            vertices.append({
                {x + left, y + top},
                m_colour,
                {u1, v1}
            });
            vertices.append({
                {x + right, y + top},
                m_colour,
                {u2, v1}
            });
            vertices.append({
                {x + right, y + bottom},
                m_colour,
                {u2, v2}
            });
            vertices.append({
                {x + left, y + bottom},
                m_colour,
                {u1, v2}
            });

            x += glyph.advance;
        }

        target.draw(vertices, states);
    }
}
