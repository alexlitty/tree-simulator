#ifndef TREESIMULATOR_RESOURCE_SHADER_HPP
#define TREESIMULATOR_RESOURCE_SHADER_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    namespace Shader
    {
        extern sf::Shader ForceAlpha;

        extern sf::Shader Fisheye;

        extern sf::Shader NoiseSimple;

        namespace Fragment {
            extern sf::Shader Test;
        }
    }
}

#endif
