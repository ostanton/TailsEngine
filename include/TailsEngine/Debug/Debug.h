#pragma once
#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>

namespace sf
{
class Vertex;
class String;
}

namespace tails
{
class Debug
{
    friend class ApplicationWindow;
    
public:
    static void log(const std::string& string);
    static void log(const char* string);
    static void log(const sf::String& string);

    static void drawLine(const sf::Vector2f& start, const sf::Vector2f& end);
    static void drawLine(float startX, float startY, float endX, float endY);

private:
    static std::vector<std::array<sf::Vertex, 2>> m_lines;
};

}
