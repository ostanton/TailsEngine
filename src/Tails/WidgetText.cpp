#include <Tails/WidgetText.hpp>
#include <Tails/FontAsset.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    WText::WText()
    {
        m_text.setString("Text");
        m_text.setCharacterSize(16);
    }

    void WText::setText(const sf::String& text)
    {
        m_text.setString(std::move(text));
    }

    const sf::String& WText::getText() const
    {
        return m_text.getString();
    }

    void WText::setFont(std::shared_ptr<CFontAsset> font)
    {
        m_font = font;
        m_text.setFont(*font);
    }

    std::shared_ptr<CFontAsset> WText::getFont() const
    {
        return m_font;
    }

    void WText::setCharacterSize(unsigned int size)
    {
        m_text.setCharacterSize(size);
    }

    unsigned int WText::getCharacterSize() const
    {
        return m_text.getCharacterSize();
    }

    void WText::setLineSpacing(float factor)
    {
        m_text.setLineSpacing(factor);
    }

    float WText::getLineSpacing() const
    {
        return m_text.getLineSpacing();
    }

    void WText::setLetterSpacing(float factor)
    {
        m_text.setLetterSpacing(factor);
    }

    float WText::getLetterSpacing() const
    {
        return m_text.getLetterSpacing();
    }

    void WText::setFillColour(const sf::Color& colour)
    {
        m_text.setFillColor(colour);
    }

    const sf::Color& WText::getFillColour() const
    {
        return m_text.getFillColor();
    }

    void WText::setOutlineColour(const sf::Color& colour)
    {
        m_text.setOutlineColor(colour);
    }

    const sf::Color& WText::getOutlineColour() const
    {
        return m_text.getOutlineColor();
    }

    void WText::setOutlineThickness(float thickness)
    {
        m_text.setOutlineThickness(thickness);
    }

    float WText::getOutlineThickness() const
    {
        return m_text.getOutlineThickness();
    }

    void WText::setStyle(sf::Text::Style style)
    {
        m_text.setStyle(style);
    }

    unsigned int WText::getStyle() const
    {
        return m_text.getStyle();
    }

    void WText::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_text, states);
    }
}
