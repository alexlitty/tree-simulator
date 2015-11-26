#include <tree/Math.hpp>
#include <tree/Object/NuggetLaser.hpp>
#include <tree/Object/Planet.hpp>

// Constructor.
tree::NuggetLaser::NuggetLaser(tree::Physical *parent)
: m_parent(parent),
  m_nozzle(2.0f, 3)
{
    // Prepare the nozzle.
    m_nozzle.setFillColor(sf::Color::Red);
    tree::Math::centerOrigin(m_nozzle);
}

// Act.
bool tree::NuggetLaser::act(tree::Stage &stage)
{
    // Update nozzle.
    m_nozzle.setRotation(m_parent->getAngle());
    m_nozzle.setPosition(
        tree::Math::vector(
            m_parent->getPosition()
        )
    );

    // Fire laser.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (m_cooldown.getElapsedTime().asSeconds() > 1) {
            m_cooldown.restart();

            // Create planet.
            tree::Planet *planet = new tree::Planet(
                m_parent->getAngledPosition(5.0f),
                stage.nugget
            );

            // Set planet velocity.
            b2Vec2 velocity = m_parent->getLinearVelocity();
            velocity = tree::Math::setMagnitude(
                velocity,
                tree::Math::magnitude(velocity) + 10.0f
            );
            planet->setLinearVelocity(velocity);

            // Add planet.
            stage.add(planet);
        }
    }

    return true;
}

// Draw.
void tree::NuggetLaser::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_nozzle, states);
}
