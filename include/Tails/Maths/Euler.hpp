#ifndef TAILS_EULER_ANGLES_HPP
#define TAILS_EULER_ANGLES_HPP

#include <Tails/Config.hpp>
#include <Tails/Concepts.hpp>

namespace tails
{
    template<FloatingPoint T>
    struct TEuler final
    {
        T pitch;
        T yaw;
        T roll;

        // TODO - from quaternion stuff
    };

    TAILS_API using SEulerf32 = TEuler<f32>;
    TAILS_API using SEulerf64 = TEuler<f64>;

    TAILS_API using SEulerf = SEulerf32;
    TAILS_API using SEulerd = SEulerf64;
}

#endif // TAILS_EULER_ANGLES_HPP
