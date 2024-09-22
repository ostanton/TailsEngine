#ifndef TAILS_CONCEPTS_HPP
#define TAILS_CONCEPTS_HPP

#include <type_traits>
#include <ostream>

namespace tails
{
    class CObject;
    class CEntity;
    
    template<typename T>
    concept UserType = std::is_class_v<T>;

    /**
     * Checks if a type can be printed via streams
     */
    template<typename T>
    concept PrintableStream = requires(T obj, std::ostream& os)
    {
        {os << obj} -> std::same_as<std::ostream&>;
    };

    template<typename... Ts>
    concept PrintableStreamAll = (PrintableStream<Ts> && ...);

    template<typename T>
    concept DerivesObject = std::derived_from<T, CObject>;

    template<typename T>
    concept DerivesEntity = std::derived_from<T, CEntity>;
}

#endif // TAILS_CONCEPTS_HPP
