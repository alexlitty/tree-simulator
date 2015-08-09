#include <tree/Math/Geometry.hpp>
#include <tree/Object/Planet.hpp>

// @@@
#include <iostream>

// Constructor.
tree::Planet::Planet()
{
    m_shape.setSize(sf::Vector2f(1000, 1000));
    m_shape.setFillColor(sf::Color::Red);
    Math::centerOrigin(m_shape);
}

// Draw the planet.
void tree::Planet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //states.transform *= getPhysicalTransform();
    target.draw(m_shape, states);
}
