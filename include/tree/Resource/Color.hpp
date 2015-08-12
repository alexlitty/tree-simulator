#ifndef TREESIMULATOR_RESOURCE_COLOR_HPP
#define TREESIMULATOR_RESOURCE_COLOR_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    namespace palette
    {
        extern const unsigned char random;
        extern const unsigned char fire;
    }

    // Generate a color, based on a predefined palette.
    sf::Color paletteColor(const unsigned char palette);
}

#endif
