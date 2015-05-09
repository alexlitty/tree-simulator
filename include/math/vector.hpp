#ifndef TREESIMULATOR_MATH_VECTOR
#define TREESIMULATOR_MATH_VECTOR

#include <SFML/Graphics.hpp>

namespace tree
{
    namespace math
    {
        /**
         * Computes the magnitude of a vector.
         */
        float magnitude(sf::Vector2f& vector);

        /**
         * Changes the magnitude of a vector.
         */
        sf::Vector2f set_magnitude(sf::Vector2f vector, float magnitude);

        /**
         * Finds the angle of a vector's direction.
         */
        float get_angle(sf::Vector2f& vector);

        /**
         * Computes a vector given an angle and magnitude.
         */
        sf::Vector2f angled_vector(float angle, float magnitude);

        /**
         * Calculates the dot product of two vectors.
         */
        float dot(sf::Vector2f& left, sf::Vector2f& right);

        /**
         * Calculates the cross product of two vectors.
         */
        float cross(sf::Vector2f& left, sf::Vector2f& right);
    }
}

#endif
