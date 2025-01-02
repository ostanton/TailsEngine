#include <Tails/Components/TextComponent.hpp>
#include <Tails/Resources/Font.hpp>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace tails
{
    CTextComponent::CTextComponent(
        CLocaleString string,
        const std::shared_ptr<CFont>& font,
        const unsigned int characterSize,
        const sf::Color colour,
        const std::uint8_t style,
        const float letterSpacing,
        const float italicShear
    ) :
        m_string(std::move(string)),
        m_font(font),
        m_underlying(m_font->getUnderlying<sf::Font>()),
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

    void CTextComponent::setFont(const std::shared_ptr<CFont>& font)
    {
        m_font = font;
        if (m_font)
            m_underlying = m_font->getUnderlying<sf::Font>();
    }

    std::shared_ptr<CFont> CTextComponent::getFont() const
    {
        return m_font;
    }

    void CTextComponent::setColour(const sf::Color colour)
    {
        m_colour = colour;
    }

    void CTextComponent::setCharacterSize(const unsigned int characterSize)
    {
        m_characterSize = characterSize;
    }

    void CTextComponent::setStyle(const std::uint8_t style)
    {
        m_style = style;
    }

    void CTextComponent::setItalicShear(const float shear)
    {
        m_italicShear = shear;
    }

    void CTextComponent::setLetterSpacing(const float spacing)
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
        if (m_underlying)
            states.texture = &m_underlying->getTexture(m_characterSize);
        else
            states.texture = nullptr;
        states.coordinateType = sf::CoordinateType::Pixels;

        // TODO - optimise or something idk
        sf::VertexArray vertices {sf::PrimitiveType::TriangleStrip};
        float x {0.f};
        float y {0.f};
        
        for (const auto strChar : m_string)
        {
            auto& glyph = m_underlying->getGlyph(strChar, m_characterSize, isBold());
            // TODO - support multi-line, etc.
            
            const float left {glyph.bounds.position.x};
            const float top {glyph.bounds.position.y};
            const float right {left + glyph.bounds.size.x};
            const float bottom {top + glyph.bounds.size.y};
            
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
