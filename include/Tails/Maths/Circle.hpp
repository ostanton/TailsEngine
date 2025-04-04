#ifndef TAILS_CIRCLE_HPP
#define TAILS_CIRCLE_HPP

#include <Tails/Maths/Vector2.hpp>

namespace tails
{
    template<typename T>
    struct TCircle final
    {
        T radius;
        TVector2<T> position;
    };

    using SFloatCircle = TCircle<float>;
    using SIntCircle = TCircle<int>;
}

#endif // TAILS_CIRCLE_HPP
