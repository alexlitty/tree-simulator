#ifndef TREESIMULATOR_MATH_SHAPE_HPP
#define TREESIMULATOR_MATH_SHAPE_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    /**
     * Finds the center point of a rectangle.
     */
    sf::Vector2f getCenter(sf::FloatRect rect);

    /**
     * Finds the center point of a vertex array.
     */
    sf::Vector2f getCenter(sf::VertexArray array);

    /**
     * Centers the origin of an SFML object.
     */
    template <typename T>
    void centerOrigin(T& object)
    {
        object.setOrigin(getCenter(object.getLocalBounds()));
    }
}

#endif
