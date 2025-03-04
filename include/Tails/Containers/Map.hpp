#ifndef TAILS_UNORDERED_MAP_HPP
#define TAILS_UNORDERED_MAP_HPP

#include <unordered_map>
#include <map>

namespace tails
{
    template<typename KeyT, typename ValueT>
    using TUnorderedMap = std::unordered_map<KeyT, ValueT>;

    template<typename KeyT, typename ValueT>
    using TOrderedMap = std::map<KeyT, ValueT>;

    template<typename KeyT, typename ValueT>
    using TMap = TUnorderedMap<KeyT, ValueT>;
}

#endif // TAILS_UNORDERED_MAP_HPP
