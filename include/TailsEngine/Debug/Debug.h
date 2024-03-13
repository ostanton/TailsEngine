#pragma once
#include <string>

namespace sf
{
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
};

}
