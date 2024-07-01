#ifndef TAILS_TRANSFORM_HPP
#define TAILS_TRANSFORM_HPP

#include <Tails/Config.hpp>

#include <SFML/System/Vector2.hpp>

#include <sstream>

namespace tails
{
    // just a group of members specific to something's transformation
    struct TAILS_API Transform
    {
        Transform() = default;
        Transform(
                const sf::Vector2f& inPos, float inRot, const sf::Vector2f& inScale = {1.f, 1.f}
            ) : position(inPos), rotation(inRot), scale(inScale) {}

        sf::Vector2f position;
        float rotation {0.f};
        sf::Vector2f scale {1.f, 1.f};

        [[nodiscard]] std::string toString() const
        {
            std::stringstream result;
            result << "\nTransform:\n";
            result << "Position: " << position.x << "x" << position.y << "\n";
            result << "Rotation: " << rotation << "\n";
            result << "Scale: " << scale.x << "x" << scale.y << "\n";
            return result.str();
        }
    };
} // tails

#endif //TAILS_TRANSFORM_HPP
