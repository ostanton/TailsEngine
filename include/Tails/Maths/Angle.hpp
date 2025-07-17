#ifndef TAILS_ANGLE_HPP
#define TAILS_ANGLE_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Maths.hpp>
#include <Tails/Maths/Vector2.hpp>

#include <compare>

namespace tails
{
    /**
     * Abstraction over an angle to allow easy use and conversion between radians and degrees
     *
     * TODO - wrap around when overflowing 360 degrees or 2pi
     * @tparam T Floating-point type
     */
    template<typename T>
    struct TAngle
    {
        constexpr TAngle() = default;
        explicit constexpr TAngle(const T radians)
            : m_angle(radians)
        {}

        static const TAngle identity;

        /**
         * Creates an angle object from the given radians
         * @param inRadians In radians
         * @return Created angle
         */
        static constexpr TAngle radians(const T inRadians) noexcept
        {
            return TAngle {inRadians};
        }

        /**
         * Creates an angle object from the given degrees
         * @param inDegrees In degrees
         * @return Created angle
         */
        static constexpr TAngle degrees(const T inDegrees) noexcept
        {
            return TAngle {maths::degToRad(inDegrees)};
        }

        /**
         * Gets the angle as a scalar in radians
         * @return Angle in radians
         */
        [[nodiscard]] constexpr T asRadians() const noexcept {return m_angle;}

        /**
         * Gets the angle as a scalar in degrees
         * @return Angle in degrees
         */
        [[nodiscard]] constexpr T asDegrees() const noexcept {return maths::radToDeg(m_angle);}

        /**
         * Gets this angle as a 2D unit vector
         * @return Angle as a unit vector
         */
        [[nodiscard]] constexpr TVector2<T> unitVector() const noexcept
        {
            // invert Y to match world coordinates (+Y up)
            return {std::cos(m_angle), -std::sin(m_angle)};
        }

        constexpr auto operator<=>(const TAngle& other) const noexcept = default;

        template<typename U>
        constexpr TAngle operator+(const TAngle<U>& other) const noexcept
        {
            return TAngle {m_angle + other.m_angle};
        }

        template<typename U>
        constexpr TAngle operator-(const TAngle<U>& other) const noexcept
        {
            return TAngle {m_angle - other.m_angle};
        }

        template<typename U>
        constexpr TAngle& operator+=(const TAngle<U>& other) noexcept
        {
            m_angle += other.m_angle;
            return *this;
        }

    private:
        /** The angle in radians */
        T m_angle {static_cast<T>(0)};
    };

    template<typename T>
    const TAngle<T> TAngle<T>::identity {};

    using SFloatAngle = TAngle<float>;
    using SDoubleAngle = TAngle<double>;
}

#endif // TAILS_ANGLE_HPP
