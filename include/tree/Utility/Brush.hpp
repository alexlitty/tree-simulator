#ifndef TREESIMULATOR_UTILITY_BRUSH_HPP
#define TREESIMULATOR_UTILITY_BRUSH_HPP

#include <SFML/Graphics.hpp>
#include <tree/Resource/Color.hpp>

namespace tree
{
    namespace brush
    {
        extern tree::palette palette;

        void spots(sf::RenderTarget *target, unsigned int count, float minRadius, float maxRadius);
    }
}

#endif
