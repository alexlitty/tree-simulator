#ifndef TREESIMULATOR_MATH_VECTOR
#define TREESIMULATOR_MATH_VECTOR

#include <SFML/Graphics.hpp>

namespace tree
{
    namespace Math
    {
        /**
         * Computes the magnitude of a vector.
         */
        float magnitude(sf::Vector2f& vector);

        /**
         * Changes the magnitude of a vector.
         */
        sf::Vector2f setMagnitude(sf::Vector2f vector, float magnitude);

        /**
         * Finds the angle of a vector's direction.
         */
        float getAngle(sf::Vector2f& vector);

        /**
         * Computes a vector given an angle and magnitude.
         */
        sf::Vector2f createVector(float angle, float magnitude);

        /**
         * Calculates the dot product of two vectors.
         */
        float dot(sf::Vector2f& left, sf::Vector2f& right);

        /**
         * Calculates the cross product of two vectors.
         */
        float cross(sf::Vector2f& left, sf::Vector2f& right);

        /**
         * Calculates the normal of a vector.
         */
        sf::Vector2f normal(sf::Vector2f& a, sf::Vector2f& b, bool topRight);
    }
}

#endif
