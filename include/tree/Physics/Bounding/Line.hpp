#ifndef TREESIMULATOR_PHYSICS_BOUNDING_LINE
#define TREESIMULATOR_PHYSICS_BOUNDING_LINE

#include <SFML/Graphics.hpp>

namespace tree
{
    struct Line
    {
        sf::Vector2f start;
        sf::Vector2f end;

        /**
         * Default constructor.
         */
        Line();

        /**
         * Constructor.
         */
        Line(sf::Vector2f& initStart, sf::Vector2f& initEnd);
    };
}

#endif
