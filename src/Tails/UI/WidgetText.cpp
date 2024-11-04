#include <Tails/UI/WidgetText.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Font.hpp>

namespace tails
{
    WText::WText(CLocaleString text, unsigned int characterSize)
        : m_string(std::move(text)), m_characterSize(characterSize)
    {
    }

    void WText::setText(const CLocaleString& text)
    {
        m_string = text;
    }

    const CLocaleString& WText::getText() const
    {
        return m_string;
    }

    void WText::setFont(sf::Font* font)
    {
        m_font = font;
    }

    sf::Font* WText::getFont() const
    {
        return m_font;
    }

    void WText::setCharacterSize(unsigned int size)
    {
        m_characterSize = size;
    }

    unsigned int WText::getCharacterSize() const
    {
        return m_characterSize;
    }

    void WText::setFillColour(const sf::Color& colour)
    {
        m_colour = colour;
    }

    const sf::Color& WText::getFillColour() const
    {
        return m_colour;
    }
    
    void WText::setOutlineThickness(float thickness)
    {
        m_outlineThickness = thickness;
    }

    float WText::getOutlineThickness() const
    {
        return m_outlineThickness;
    }

    void WText::setBold(bool bold)
    {
        m_bold = bold;
    }

    unsigned int WText::getBold() const
    {
        return m_bold;
    }

    void WText::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (!m_font) return;
        
        states.transform *= getTransform();
        
        for (auto stringChar : m_string)
        {
            auto& glyph = m_font->getGlyph(stringChar, m_characterSize, m_bold, m_outlineThickness);
            sf::VertexArray character {sf::PrimitiveType::TriangleStrip, 4};
            character[1].texCoords = {0.f, static_cast<float>(glyph.textureRect.size.y)};
            character[2].texCoords = {static_cast<float>(glyph.textureRect.size.x), 0.f};
            character[3].texCoords = {
                static_cast<float>(glyph.textureRect.size.x),
                static_cast<float>(glyph.textureRect.size.y)
            };
            
            states.texture = &m_font->getTexture(m_characterSize);
            
            target.draw(character, states);
        }
    }

    void WText::setSize(const sf::Vector2f& size)
    {

    }

    std::optional<sf::Vector2f> WText::getSize() const
    {
        if (!m_font) return std::nullopt;
        
        sf::Vector2f size;
        
        for (auto stringChar : m_string)
        {
            size += m_font->getGlyph(stringChar, m_characterSize, m_bold, m_outlineThickness).bounds.size;
        }
        
        return std::make_optional(size);
    }
}
