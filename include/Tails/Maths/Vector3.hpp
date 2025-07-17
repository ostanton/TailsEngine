#ifndef TAILS_VECTOR3_HPP
#define TAILS_VECTOR3_HPP

#include <Tails/Core.hpp>

namespace tails
{
    /**
     * 3-dimensional vector
     * @tparam T Arithmetic type
     */
    template<typename T>
    struct TVector3 final
    {
        T x;
        T y;
        T z;
    };

    using SVector3f = TVector3<float>;
    using SVector3d = TVector3<double>;
    using SVector3i = TVector3<int>;
    using SVector3u = TVector3<unsigned int>;
}

#endif // TAILS_VECTOR3_HPP
