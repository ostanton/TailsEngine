#include "TailsEngine/Debug/Debug.h"

#include <array>
#include <iostream>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/String.hpp>

void tails::Debug::log(const std::string& string)
{
    std::cout << string << "\n";
}

void tails::Debug::log(const char* string)
{
    std::cout << string << "\n";
}

void tails::Debug::log(const sf::String& string)
{
    log(string.toAnsiString());
}

void tails::Debug::drawLine(const sf::Vector2f& start, const sf::Vector2f& end)
{
    const std::array<sf::Vertex, 2> resultLine {sf::Vertex(start), sf::Vertex(end)};
    m_lines.push_back(resultLine);
}

void tails::Debug::drawLine(float startX, float startY, float endX, float endY)
{
    drawLine(sf::Vector2f(startX, startY), sf::Vector2f(endX, endY));
}
