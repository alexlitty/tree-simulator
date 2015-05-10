#ifndef TREESIMULATOR_PHYSICS_INTERSECT_HPP
#define TREESIMULATOR_PHYSICS_INTERSECT_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    namespace Intersect
    {
    bool lines(sf::Vector2f& A, sf::Vector2f& B, sf::Vector2f& C, sf::Vector2f& D, sf::Vector2f& result);
    //    bool intersect(tree::Bounding::Box& box, sf::Vector2f& A, sf::Vector2f& B, sf::Vector2f& result);
//    bool intersect(tree::Bounding::Box& box, sf::Vector2f& point);
//    bool intersect(sf::FloatRect A, sf::FloatRect B);
    }
}

#endif
