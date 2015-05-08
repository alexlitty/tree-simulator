#include <math/geometry.hpp>
#include <math/vector.hpp>
#include <object/player.hpp>

// Constructor.
tree::player::player()
: tree::lifeform::lifeform(10),
  m_rotation_power(4),
  m_velocity_power(0.1f)
{
    m_shape.setSize(sf::Vector2f(20, 10));
    m_shape.setFillColor(sf::Color::Green);

    math::center_origin(m_shape);
    mass = 1000;
}

// Perform a thrust.
void tree::player::thrust(bool direction)
{
    sf::Vector2f delta = math::angled_vector(
        get_rotation(),
        m_velocity_power
    );

    if (direction) {
        velocity += delta;
    } else {
        velocity -= delta;
    }
}

// Perform a rotation.
void tree::player::rotate(bool direction)
{
    physical::rotate(direction ? m_rotation_power : -m_rotation_power);
}

// Draw the player.
void tree::player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= get_physical_transform();
    target.draw(m_shape, states);
}
