#include <tree/Math/Constant.hpp>
#include <tree/Math/Trigonometry.hpp>
#include <tree/Math/Vector.hpp>

/**
 * Calculates the angle made by two points.
 */
tree::Angle tree::GetAngle(Point &a, Point &b)
{
    Point sub = a - b;

    // Prevent division by zero.
    if (sub.x == 0 || sub.y == 0) {
        return 0.0f;
    }

    // Return angle.
    return std::atan2(sub.y, sub.x);
}

/**
 * @deprecated
 */
float tree::Math::radians(float degrees)
{
    return tree::angle((degrees * tree::Math::PI) / 180.0f);
}

/**
 * @deprecated
 */
float tree::Math::degrees(float radians)
{
    return tree::angle(
        (radians * 180.0f) / tree::Math::PI,
        false
    );
}
