#ifndef TAILS_DYNAMIC_ARRAY_HPP
#define TAILS_DYNAMIC_ARRAY_HPP

// TODO - allow different implementations of the array or something
// do we want a wrapper like with SFML and Win32 stuff?
// template<typename T> class TArray {std::vector<T> m_vector;};
// so we can have our own interface for it? or just assume everything is standard interface?
// I think use our own interface, not the standard. Make it more use-friendly

#include <vector>

namespace tails
{
    template<typename T>
    using TArray = std::vector<T>;
}

#endif // TAILS_DYNAMIC_ARRAY_HPP
