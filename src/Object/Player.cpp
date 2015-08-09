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

    // Initialize hat.
    hatColor = sf::Color::Magenta;
    m_hat.setSize(sf::Vector2f(5, 10));
    m_hat.move(sf::Vector2f(16, 0));
    m_hat.setFillColor(hatColor);
    Math::centerOrigin(m_shape);
    m_hat.setOrigin(m_shape.getOrigin());
}

// Perform a thrust.
void tree::Player::thrust(bool direction)
{
}

// Perform a rotation.
void tree::Player::rotate(bool direction)
{
}

// Draw the player.
void tree::Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //states.transform *= getPhysicalTransform();
    target.draw(m_shape, states);
    target.draw(m_hat, states);
}
