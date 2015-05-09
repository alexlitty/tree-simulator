#include <math/geometry.hpp>
#include <object/planet.hpp>

// Constructor.
tree::planet::planet()
: m_shape(50, 30)
{
    m_shape.setFillColor(sf::Color::Red);
    math::center_origin(m_shape);
}

// Draw the planet.
void tree::planet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= get_physical_transform();
    target.draw(m_shape, states);
}
