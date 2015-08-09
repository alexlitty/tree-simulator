#ifndef TREESIMULATOR_MATH_GEOMETRY_HPP
#define TREESIMULATOR_MATH_GEOMETRY_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    namespace Math
    {
        /**
         * Finds the distance between two vectors.
         */
        float distance(sf::Vector2f left, sf::Vector2f right);

        /**
         * Finds the center point of a rectangle.
         */
        sf::Vector2f getCenter(sf::FloatRect rect);

        /**
         * Finds the center point between two vectors.
         */
        sf::Vector2f center(sf::Vector2f left, sf::Vector2f right);

        /**
         * Centers the origin of a shape.
         */
        void centerOrigin(sf::Shape& object);
    }
}

#endif
