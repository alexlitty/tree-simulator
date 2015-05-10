#include <tree/Math/Geometry.hpp>
#include <tree/Math/Vector.hpp>
#include <tree/Object/Player.hpp>

// Constructor.
tree::Player::Player()
: tree::Lifeform::Lifeform(10),
  m_rotationPower(4),
  m_velocityPower(300.0f)
{
    // Initialize shape.
    m_shape.setSize(sf::Vector2f(20, 10));
    m_shape.setFillColor(sf::Color::Green);
    Math::centerOrigin(m_shape);

    // Initialize boundary.
    tree::Bounding::Box box(m_shape.getLocalBounds());
    boundary.set(box);

    // Other physics options.
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
        accelerate(delta);
    } else {
        delta = -delta;
        accelerate(delta);
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
}
