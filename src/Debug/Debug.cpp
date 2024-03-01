#include "TailsEngine/Debug/Debug.h"

#include <iostream>

void tails::Debug::log(const std::string& string)
{
    std::cout << string << "\n";
}
