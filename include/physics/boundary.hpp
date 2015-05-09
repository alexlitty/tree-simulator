#ifndef TREESIMULATOR_PHYSICS_BOUNDARY_BOX_HPP
#define TREESIMULATOR_PHYSICS_BOUNDARY_BOX_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    /**
     * Boundary implementations.
     */
    class Boundary
    {
    public:
        
        // Representation of boundary types.
        enum class TYPE
        {
            LINE,
            BOX,
            ELLIPSE,
        };

        // Type of boundary.
        TYPE type; 

        /**
         * Checks if this boundary collides with another boundary.
         *
         * Result is filled with the intersection point.
         */
        bool Collides(Boundary& other, sf::Vector2f& result);
    };
}

#endif
