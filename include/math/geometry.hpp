#ifndef TREESIMULATOR_MATH_GEOMETRY_HPP
#define TREESIMULATOR_MATH_GEOMETRY_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    namespace math
    {
        /**
         * Finds the distance between two vectors.
         */
        float distance(sf::Vector2f left, sf::Vector2f right);

        /**
         * Finds the center point of a rectangle.
         */
        sf::Vector2f get_center(sf::FloatRect rect);

        /**
         * Centers the origin of a shape.
         */
        void center_origin(sf::Shape& object);
    }
}

#endif
