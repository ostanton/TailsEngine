#include "TailsEngine/Debug/Debug.h"

#include <iostream>
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
