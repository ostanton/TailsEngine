#ifndef TAILS_VECTOR2_HPP
#define TAILS_VECTOR2_HPP

#include <SFML/System/Vector2.hpp>

#include <nlohmann/json.hpp>

namespace tails
{
    /**
     * More of a helper to aid in serialisation stuff than a type to use everywhere.
     * @tparam T Type for the vector to use
     */
    template<typename T>
    struct TVector2 final
    {
        TVector2() = default;
        TVector2(T inX, T inY) : x(inX), y(inY) {}
        TVector2(const TVector2& other)
            : x(other.x), y(other.y) {}
        TVector2(TVector2&& other) noexcept
            : x(std::move(other.x)), y(std::move(other.y)) {}
        explicit TVector2(const sf::Vector2<T>& other)
            : x(other.x), y(other.y) {}
        explicit TVector2(sf::Vector2<T>&& other) noexcept // TODO - noexcept applies here???
            : x(std::move(other).x), y(std::move(other).y) {}
        ~TVector2() = default;

        // TODO - better to default these and not specify stuff??
        
        TVector2& operator=(const TVector2& other)
        {
            if (other != *this)
            {
                x = other.x;
                y = other.y;
            }
            return *this;
        }

        TVector2& operator=(TVector2&& other) noexcept
        {
            if (other != *this)
            {
                x = std::move(other.x);
                y = std::move(other.y);
            }

            return *this;
        }

        TVector2& operator=(const sf::Vector2<T>& other)
        {
            x = other.x;
            y = other.y;
            return *this;
        }

        TVector2& operator=(sf::Vector2<T>&& other) noexcept // TODO - same here??
        {
            x = std::move(other.x);
            y = std::move(other.y);
            return *this;
        }

        [[nodiscard]] sf::Vector2<T> createSF() const
        {
            return {x, y};
        }

        operator sf::Vector2<T>() const
        {
            return createSF();
        }

        bool operator==(const TVector2& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const TVector2& other) const
        {
            return !(*this == other);
        }

        bool operator==(const sf::Vector2<T>& other) const
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const sf::Vector2<T>& other) const
        {
            return !(*this == other);
        }

        [[nodiscard]] std::string toString() const
        {
            return std::to_string(x) + "x" + std::to_string(y);
        }

        [[nodiscard]] static std::string toString(const sf::Vector2<T>& other)
        {
            return std::to_string(other.x) + "x" + std::to_string(other.y);
        }
        
        [[nodiscard]] static nlohmann::json toJSON(const sf::Vector2<T>& other)
        {
            nlohmann::json obj;
            obj.push_back("x");
            obj.push_back("y");
            obj["x"] = other.x;
            obj["y"] = other.y;
            return obj;
        }

        [[nodiscard]] static TVector2 fromJSON(const nlohmann::json& obj)
        {
            return {obj["x"].get<T>(), obj["y"].get<T>()};
        }

        T x;
        T y;
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const TVector2<T>& vector)
    {
        os << vector.x << "x" << vector.y;
        return os;
    }

    using SVector2f = TVector2<float>;
    using SVector2i = TVector2<int>;
    using SVector2u = TVector2<unsigned int>;
}

#endif // TAILS_VECTOR2_HPP
