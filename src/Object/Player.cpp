#include <tree/Engine/Constant.hpp>
#include <tree/Math/Constant.hpp>
#include <tree/Math/Geometry.hpp>
#include <tree/Math/Random.hpp>
#include <tree/Math/Vector.hpp>
#include <tree/Object/Player.hpp>
#include <tree/Resource/Color.hpp>

// Constructor.
tree::Player::Player()
: tree::Lifeform::Lifeform(10),
  m_rotationPower(0.1f),
  m_velocityPower(0.0025f),
  engineParticles(200, 1500)
{
    // Initialize shape.
    m_shape.setSize(sf::Vector2f(0.02, 0.01));
    m_shape.setFillColor(sf::Color::Green);
    Math::centerOrigin(m_shape);

    // Initialize hat.
    hatColor = sf::Color::Magenta;
    m_hat.setSize(sf::Vector2f(0.005, 0.01));
    m_hat.move(sf::Vector2f(0.016, 0));
    m_hat.setFillColor(hatColor);
    Math::centerOrigin(m_shape);
    m_hat.setOrigin(m_shape.getOrigin());

    // Physical body definition.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 100.0f;
    bodyDef.fixedRotation = false;
    setBody(bodyDef);

    // Physical shape.
    b2PolygonShape pShape;
    pShape.SetAsBox(0.02, 0.01);

    // Physical fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &pShape;
    fixtureDef.density = 2.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.filter.categoryBits = tree::COLLISION_NORMAL;
    fixtureDef.filter.maskBits = tree::COLLISION_WORLD;
    m_body->CreateFixture(&fixtureDef);
}

// Perform a thrust.
void tree::Player::thrust(bool direction)
{
    m_body->ApplyForceToCenter(
            tree::Math::createVector(
                m_body->GetAngle(),
            direction ? m_velocityPower : -m_velocityPower
        ), true
    );

    b2Vec2 baseEngineVector = this->getPosition() - tree::Math::createVector(this->getAngle(), 0.01f);

    for (unsigned int j = 0; j < 2; j++) {
        float displacement = tree::random(0.000f, 0.005f);

        for (unsigned int i = 0; i < 2; i++) {

            b2Vec2 engineVector = baseEngineVector - tree::Math::createVector(
                m_body->GetAngle() - (tree::Math::PI / 2),
                (i == 0) ? -displacement : displacement
            );

            engineParticles.add(
                engineVector,
                this->getLinearVelocity() + tree::Math::createVector(
                    this->getAngle() + (((i==0) ? 1 : -1) * tree::random(-0.5f, 0.785f)),
                    200 * (direction ? -m_velocityPower : m_velocityPower)
                ),
                tree::paletteColor(palette::fire)
            );
        }
    }
}

// Perform a rotation.
void tree::Player::rotate(bool direction)
{
    this->addAngle(
        (direction ? m_rotationPower : -m_rotationPower)
    );
}

// Draw the player.
void tree::Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(engineParticles, states);

    addPhysicalTransform(states.transform);
    target.draw(m_shape, states);
    target.draw(m_hat, states);
}
