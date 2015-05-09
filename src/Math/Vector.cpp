#include <cmath>
#include <tree/Math/Vector.hpp>
#include <tree/Math/Trigonometry.hpp>

// Computes the magnitude of a vector.
float tree::Math::magnitude(sf::Vector2f& vector)
{
    return std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}

// Changes the magnitude of a vector.
sf::Vector2f tree::Math::setMagnitude(sf::Vector2f vector, float magnitude)
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
float tree::Math::getAngle(sf::Vector2f& vector)
{
    // Reference vector, where 0 degrees is.
    sf::Vector2f start(1.0f, 0);

    float result = tree::Math::dot(vector, start);
    result /= tree::Math::magnitude(vector) * tree::Math::magnitude(start);
    return std::acos(result);
}

// Computes a vector given an angle and magnitude.
sf::Vector2f tree::Math::createVector(float angle, float magnitude)
{
    return sf::Vector2f(
        magnitude * std::cos(Math::radians(angle)),
        magnitude * std::sin(Math::radians(angle))
    );
}

// Calculates the dot product of two vectors.
float tree::Math::dot(sf::Vector2f& left, sf::Vector2f& right)
{
    return (left.x * right.x) + (left.y * right.y);
}

// Calculates the cross product of two vectors.
float tree::Math::cross(sf::Vector2f& left, sf::Vector2f& right)
{
    return (left.x * right.y) - (left.y * right.x);
}
