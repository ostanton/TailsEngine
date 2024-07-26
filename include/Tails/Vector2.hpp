#ifndef TAILS_VECTOR2_HPP
#define TAILS_VECTOR2_HPP

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace tails
{
    /**
     * 2D vector structure that provides conversions to and from sf::Vector2 and helpful methods that SFML's
     * Vector2 does not. Use over sf::Vector2 when possible (although it doesn't matter too much)
     * @tparam T Vector type
     */
    template<typename T>
    struct Vector2
    {
        Vector2() = default;

        explicit Vector2(T value) : x(value), y(value) {}
        explicit Vector2(const sf::Vector2<T>& other) : x(other.x), y(other.y) {}
        template<typename U>
        explicit Vector2(const Vector2<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

        Vector2(T inX, T inY) : x(inX), y(inY) {}
        Vector2(const Vector2<T>& other) : x(other.x), y(other.y) {}

        ~Vector2() = default;

        Vector2& operator=(const Vector2& other)
        {
            if (*this != other)
            {
                x = other.x;
                y = other.y;
            }

            return *this;
        }

        Vector2& operator=(const sf::Vector2<T>& other)
        {
            x = other.x;
            y = other.y;

            return *this;
        }

        bool operator==(const Vector2& other)
        {
            return x == other.x && y == other.y;
        }

        bool operator==(const sf::Vector2<T>& other)
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const Vector2& other)
        {
            return !(*this == other);
        }

        bool operator!=(const sf::Vector2<T>& other)
        {
            return !(*this == other);
        }

        /**
         * Gets the SFML Vector2 representation
         * @return SFML Vector2
         */
        [[nodiscard]] sf::Vector2<T> get() const {return {x, y};}

        /* Helper methods */

        template<typename U = T>
        [[nodiscard]] U length()
        {
            auto U_x = static_cast<U>(x);
            auto U_y = static_cast<U>(y);

            return std::sqrt(U_x * U_x + U_y * U_y);
        }

        /* Members */

        T x;
        T y;
    };

    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int>;
    using Vector2u = Vector2<unsigned int>;
}

#endif //TAILS_VECTOR2_HPP
