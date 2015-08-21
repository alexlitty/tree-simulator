#ifndef TREESIMULATOR_MATH_CONSTANT_HPP
#define TREESIMULATOR_MATH_CONSTANT_HPP

#include <SFML/System.hpp>

namespace tree
{
    extern const float PI;
    extern const float TWO_PI;
    extern const float PI_HALF;

    namespace Math
    {
        extern const float PI;

        // Gravitational constant.
        extern const float GRAVITATIONAL;

        namespace Vector
        {
            // The vector at (0, 0).
            extern const sf::Vector2f ZERO;
        }
    }
}

#endif
