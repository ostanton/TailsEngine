#ifndef TAILS_RECT_HPP
#define TAILS_RECT_HPP

#include <Tails/Maths/Vector2.hpp>

namespace tails
{
    template<typename T>
    struct TRect final
    {
        TVector2<T> position;
        TVector2<T> size;

        [[nodiscard]] bool intersects(const TRect& other) const noexcept
        {
            return position.x >= other.position.x && position.x + size.x <= other.position.x + other.size.x
                && position.y >= other.position.y && position.y + size.y <= other.position.y + other.size.y;
        }

        [[nodiscard]] bool isZero() const noexcept
        {
            return position.isZero() && size.isZero();
        }
    };

    using SFloatRect = TRect<float>;
    using SIntRect = TRect<int>;
}

#endif // TAILS_RECT_HPP
