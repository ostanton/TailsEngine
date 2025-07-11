#ifndef TAILS_TRANSFORM_2D_HPP
#define TAILS_TRANSFORM_2D_HPP

#include <Tails/Maths/Vector2.hpp>

namespace tails
{
    /**
     * TODO - make matrix transform
     * @tparam T Transform type
     */
    template<typename T>
    struct TTransform2D final
    {
        void translate(const TVector2<T> offset)
        {
            position += offset;
        }

        void rotate(const float angle) {rotation += angle;}
        void scale(const TVector2<T> factor)
        {
            scale2D += factor;
        }
        
        TVector2<T> position;
        T rotation;
        TVector2<T> scale2D;
    };

    using STransform2D = TTransform2D<float>;
}

#endif // TAILS_TRANSFORM_2D_HPP
