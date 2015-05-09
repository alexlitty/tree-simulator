#include <tree/Math/Geometry.hpp>
#include <tree/Object/Planet.hpp>

// Constructor.
tree::Planet::Planet()
: m_shape(50, 30)
{
    m_shape.setFillColor(sf::Color::Red);
    Math::centerOrigin(m_shape);
}

// Draw the planet.
void tree::Planet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getPhysicalTransform();
    target.draw(m_shape, states);
}
