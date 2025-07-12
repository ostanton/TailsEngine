#include <Tails/Maths/Matrix2D.hpp>
#include <Tails/Memory.hpp>
#include <Tails/Maths/Transform2D.hpp>

namespace tails
{
    SMatrix2D::SMatrix2D()
    {
        setIdentity();
    }

    SMatrix2D::SMatrix2D(const TTransform2D<float>& inTransform)
    {
        setPosition(inTransform.position);
        setRotation(inTransform.rotation);
        setScale(inTransform.scale2D);
    }

    void SMatrix2D::setIdentity()
    {
        mem::set(matrix, 0);
        matrix[0][0] = 1.f;
        matrix[1][1] = 1.f;
        matrix[2][2] = 1.f;
    }

    void SMatrix2D::translate(const SVector2f offset)
    {
        const float translation[3][3] = {
            {1.f, 0.f, offset.x},
            {0.f, 1.f, offset.y},
            {0.f, 0.f, 1.f},
        };
        multiply(translation);
    }

    void SMatrix2D::rotate(const float degrees)
    {

    }

    void SMatrix2D::rotateRad(const float radians)
    {
        const float cos = std::cos(radians);
        const float sin = std::sin(radians);

        const float rotation[3][3] = {
            {cos, -sin, 0.f},
            {sin, cos, 0.f},
            {0.f, 0.f, 1.f},
        };
        multiply(rotation);
    }

    void SMatrix2D::scale(const SVector2f factor)
    {
        const float scaled[3][3] = {
            {factor.x, 0.f, 0.f},
            {0.f, factor.y, 0.f},
            {0.f, 0.f, 1.f},
        };
        multiply(scaled);
    }

    SVector2f SMatrix2D::transform(const SVector2f point) const noexcept
    {
        return {
            point.x * matrix[0][0] + point.y * matrix[0][1] + matrix[0][2],
            point.x * matrix[1][0] + point.y * matrix[1][1] + matrix[1][2]
        };
    }

    void SMatrix2D::setPosition(const SVector2f position)
    {
        matrix[0][2] = position.x;
        matrix[1][2] = position.y;
    }

    void SMatrix2D::setRotation(const float degrees)
    {

    }

    void SMatrix2D::setRotationRad(const float radians)
    {
        const auto currentScale = getScale();
        const float cosA = std::cos(radians);
        const float sinA = std::sin(radians);

        matrix[0][0] = cosA * currentScale.x;
        matrix[0][1] = -sinA * currentScale.y;
        matrix[1][0] = sinA * currentScale.x;
        matrix[1][1] = cosA * currentScale.y;
    }

    void SMatrix2D::setScale(const SVector2f inScale)
    {
        const float currentAngle {getRotationRad()};
        const float cosA = std::cos(currentAngle);
        const float sinA = std::sin(currentAngle);

        matrix[0][0] = cosA * inScale.x;
        matrix[0][1] = -sinA * inScale.y;
        matrix[1][0] = sinA * inScale.x;
        matrix[1][1] = cosA * inScale.y;
    }

    SVector2f SMatrix2D::getPosition() const noexcept
    {
        return {matrix[0][2], matrix[1][2]};
    }

    float SMatrix2D::getRotation() const noexcept
    {
        return 0.f;
    }

    float SMatrix2D::getRotationRad() const noexcept
    {
        return std::atan2(matrix[1][0], matrix[0][0]);
    }

    SVector2f SMatrix2D::getScale() const noexcept
    {
        return {
            maths::sqrt(matrix[0][0] * matrix[0][0] + matrix[1][0] * matrix[1][0]),
            maths::sqrt(matrix[0][1] * matrix[0][1] + matrix[1][1] * matrix[1][1])
        };
    }

    TTransform2D<float> SMatrix2D::getTransform2D() const noexcept
    {
        return {
            .position = getPosition(),
            .rotation = getRotation(),
            .scale2D = getScale()
        };
    }

    void SMatrix2D::multiply(const float other[3][3])
    {
        float result [3][3] = {};

        for (int row {0}; row < 3; row++)
            for (int col {0}; col < 3; col++)
                for (int k {0}; k < 3; k++)
                    result[row][col] += matrix[row][k] * other[k][col];

        mem::copy(matrix, result);
    }
}
