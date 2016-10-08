#ifndef TREESIMULATOR_RESOURCE_COLOR_HPP
#define TREESIMULATOR_RESOURCE_COLOR_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    enum class palette
    {
        random,
        white,
        water,
        rock,
        fire,
        lava,
        light,
    };

    // Generate a color, based on a predefined palette.
    sf::Color paletteColor(tree::palette palette = tree::palette::random);
}

#endif
