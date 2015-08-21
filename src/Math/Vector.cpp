#include <cmath>
#include <tree/Math.hpp>

// Reduces an angle.
float tree::angle(float a)
{
    if (a <= PI && a >= -PI) {
        return a;
    }
    return a - TWO_PI * std::floor(
        (a + PI) / TWO_PI
    );
}

// Finds the angle between two vectors.
float tree::getAngle(b2Vec2 point, b2Vec2 target)
{
    b2Vec2 sub = target - point;

    // Prevent division by zero.
    if (sub.x == 0 || sub.y == 0) {
        return 0.0f;
    }

    // Return angle.
    return tree::angle(
        std::atan2(sub.y, sub.x)
    );
}

// Converts physics vectors to drawing vectors.
sf::Vector2f tree::Math::vector(const b2Vec2 &vec)
{
    return sf::Vector2f(vec.x, vec.y);
}

// Converts drawing vectors to physics vectors.
b2Vec2 tree::Math::vector(const sf::Vector2f &vec)
{
    return b2Vec2(vec.x, vec.y);
}

// Computes the magnitude of a vector.
float tree::Math::magnitude(b2Vec2 vector)
{
    return std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}

// Changes the magnitude of a vector.
b2Vec2 tree::Math::setMagnitude(b2Vec2 vector, float magnitude)
{
    float old_magnitude = tree::Math::magnitude(vector);

    // Horizontal part.
    if (vector.x != 0) {
        vector.x *= magnitude / old_magnitude;
    }

    // Vertical part.
    if (vector.y != 0) {
        vector.y *= magnitude / old_magnitude;
    }

    return vector;
}

// Finds the angle of a vector's direction.
float tree::Math::getAngle(b2Vec2 vector)
{
    // Reference vector, where 0 degrees is.
    b2Vec2 start(1.0f, 0);

    float result = tree::dot(vector, start);
    result /= tree::Math::magnitude(vector) * tree::Math::magnitude(start);
    return std::acos(result);
}

// Computes a vector given an angle and magnitude.
b2Vec2 tree::Math::createVector(float angle, float magnitude)
{
    return b2Vec2(
        magnitude * std::cos(angle),
        magnitude * std::sin(angle)
    );
}

// Calculates the dot product of two vectors.
float tree::dot(b2Vec2& left, b2Vec2& right)
{
    return (left.x * right.x) + (left.y * right.y);
}

// Calculates the cross product of two vectors.
float tree::Math::cross(b2Vec2& left, b2Vec2& right)
{
    return (left.x * right.y) - (left.y * right.x);
}

// Calculates the normal vector of a line.
b2Vec2 tree::Math::normal(b2Vec2& a, b2Vec2& b, bool topRight)
{
    b2Vec2 result(
        b.y - a.y,
        b.x - a.x
    );

    if (!topRight) {
        result.x = -result.x;
    } else {
        result.y = -result.y;
    }
    return result;
}
