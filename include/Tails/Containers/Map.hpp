#ifndef TAILS_UNORDERED_MAP_HPP
#define TAILS_UNORDERED_MAP_HPP

#include <unordered_map>

namespace tails
{
    template<typename KeyT, typename ValueT>
    using TMap = std::unordered_map<KeyT, ValueT>;
}

#endif // TAILS_UNORDERED_MAP_HPP
