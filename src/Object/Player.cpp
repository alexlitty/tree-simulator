#include <tree/Math/Geometry.hpp>
#include <tree/Math/Vector.hpp>
#include <tree/Object/Player.hpp>

// Constructor.
tree::Player::Player()
: tree::Lifeform::Lifeform(10),
  m_rotationPower(4),
  m_velocityPower(0.1f)
{
    m_shape.setSize(sf::Vector2f(20, 10));
    m_shape.setFillColor(sf::Color::Green);

    //m_shape.setSize(sf::Vector2f(5, 10));
    //_shape.setFillColor(sf::Color::Blue);
    //m_shape.setPosition(sf::Vector2f(0, 20));

    Math::centerOrigin(m_shape);
    mass = 1000;
}

// Perform a thrust.
void tree::Player::thrust(bool direction)
{
    sf::Vector2f delta = Math::createVector(
        getRotation(),
        m_velocityPower
    );

    if (direction) {
        velocity += delta;
    } else {
        velocity -= delta;
    }
}

// Perform a rotation.
void tree::Player::rotate(bool direction)
{
    Physical::rotate(direction ? m_rotationPower : -m_rotationPower);
}

// Draw the player.
void tree::Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getPhysicalTransform();
    target.draw(m_shape, states);
    //target.draw(m_hat, states);
}
