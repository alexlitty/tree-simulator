#include <cmath>
#include <math/vector.hpp>
#include <math/trigonometry.hpp>

// Computes the magnitude of a vector.
float tree::math::magnitude(sf::Vector2f& vector)
{
    return std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}

// Changes the magnitude of a vector.
sf::Vector2f tree::math::set_magnitude(sf::Vector2f vector, float magnitude)
{
    float old_magnitude = tree::math::magnitude(vector);

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
float tree::math::get_angle(sf::Vector2f& vector)
{
    // Reference vector, where 0 degrees is.
    sf::Vector2f start(1.0f, 0);

    float result = tree::math::dot(vector, start);
    result /= tree::math::magnitude(vector) * tree::math::magnitude(start);
    return std::acos(result);
}

// Computes a vector given an angle and magnitude.
sf::Vector2f tree::math::angled_vector(float angle, float magnitude)
{
    return sf::Vector2f(
        magnitude * std::cos(math::radians(angle)),
        magnitude * std::sin(math::radians(angle))
    );
}

// Calculates the dot product of two vectors.
float tree::math::dot(sf::Vector2f& left, sf::Vector2f& right)
{
    return (left.x * right.x) + (left.y * right.y);
}
