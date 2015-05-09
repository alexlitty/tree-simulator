#ifndef TREESIMULATOR_PHYSICS_INTERSECT_HPP
#define TREESIMULATOR_PHYSICS_INTERSECT_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    bool Intersect(sf::Vector2f& A, sf::Vector2f& B, sf::Vector2f& C, sf::Vector2f& D, sf::Vector2f& result);
    bool Intersect(sf::FloatRect& box, sf::Vector2f& A, sf::Vector2f& B, sf::Vector2f& result);
    bool Intersect(sf::FloatRect& box, sf::Vector2f& point);
    bool Intersect(sf::FloatRect A, sf::FloatRect B);
}

#endif
