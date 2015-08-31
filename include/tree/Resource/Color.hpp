#ifndef TREESIMULATOR_RESOURCE_COLOR_HPP
#define TREESIMULATOR_RESOURCE_COLOR_HPP

#include <SFML/Graphics.hpp>
#include <tree/Object/Nugget.hpp>

namespace tree
{
    enum class palette
    {
        random,
        rock,
        fire,
        light,
    };

    // Generate a color, based on a predefined palette.
    sf::Color paletteColor(tree::palette palette = tree::palette::random);

    // Get the palette of a nugget.
    tree::palette nuggetPalette(tree::nugget nug);

    // Generate a base nugget color.
    sf::Color nuggetColor(tree::nugget nug);
}

#endif
