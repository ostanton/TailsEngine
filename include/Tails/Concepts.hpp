#ifndef TAILS_CONCEPTS_HPP
#define TAILS_CONCEPTS_HPP

#include <type_traits>
#include <ostream>

namespace tails
{
    class CObject;
    class CEntity;
    class CComponent;
    class IBus;

    template<typename T>
    concept UserType = std::is_class_v<T>;
    
    template<typename T, typename... Ts>
    concept ConstructibleUserType = requires(T obj)
    {
        std::is_class_v<T>;
        requires std::constructible_from<T, Ts...>;
    };

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

    template<typename T>
    concept DerivesComponent = std::derived_from<T, CComponent>;

    template<typename T>
    concept DerivesBus = std::derived_from<T, IBus>;
}

#endif // TAILS_CONCEPTS_HPP
