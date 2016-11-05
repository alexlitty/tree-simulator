#ifndef TREESIMULATOR_MATH_ARC_HPP
#define TREESIMULATOR_MATH_ARC_HPP

#include <SFML/Graphics.hpp>
#include <tree/Math.hpp>

namespace tree
{
    void makeArc(sf::VertexArray &vertices, Vector start, Vector end, float magnitude, DistributionFunction dist = IdentityDistribution);
}

#endif
