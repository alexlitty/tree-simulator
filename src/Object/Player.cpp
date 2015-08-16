#include <tree/Engine/Constant.hpp>
#include <tree/Math/Constant.hpp>
#include <tree/Math/Geometry.hpp>
#include <tree/Math/Random.hpp>
#include <tree/Math/Vector.hpp>
#include <tree/Object/Branch/Birch.hpp>
#include <tree/Object/Player.hpp>
#include <tree/Resource/Color.hpp>

// Constructor.
tree::Player::Player()
: tree::Lifeform::Lifeform(10),
  m_rotationPower(0.1f),
  m_velocityPower(250000.0f),
  engineParticles(200, 1500)
{
    // Initialize shape.
    m_shape.setSize(tree::pixels(b2Vec2(2.0f, 1.0f)));
    m_shape.setFillColor(sf::Color::Green);
    //Math::centerOrigin(m_shape);

    // Initialize hat.
    hatColor = sf::Color::Magenta;
    m_hat.setSize(tree::pixels(b2Vec2(1.0f, 0.2f)));
    m_hat.move(tree::pixels(b2Vec2(0, 0.3f)));
    m_hat.setFillColor(hatColor);
    Math::centerOrigin(m_shape);
    m_hat.setOrigin(m_shape.getOrigin());

    // Physical body definition.
    b2BodyDef bodyDef;
    bodyDef.position.Set(0.0f, 0.0f);
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 100.0f;
    bodyDef.fixedRotation = true;
    setBody(bodyDef);

    // Physical shape.
    b2PolygonShape pShape;
    pShape.SetAsBox(1.0f, 0.5f);

    // Physical fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &pShape;
    fixtureDef.density = 500.0f;
    fixtureDef.friction = 0.05f;
    fixtureDef.restitution = 0.25f;
    fixtureDef.filter.categoryBits = tree::COLLISION_NORMAL;
    fixtureDef.filter.maskBits = tree::COLLISION_WORLD;
    m_body->CreateFixture(&fixtureDef);

    // Test branch.
    m_branches.push_back(
        new tree::branches::Birch(
            this->m_body,
            m_body->GetLocalPoint(getPosition() + b2Vec2(0.0f, 5.0f)),
            m_body->GetLocalPoint(getPosition())
        )
    );
}

// Destructor.
tree::Player::~Player()
{
    for (auto branch : m_branches) {
        delete branch;
    }
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

    b2Vec2 baseEngineVector = this->getPosition() - tree::Math::createVector(this->getAngle(), 0.1f);

    for (unsigned int j = 0; j < 2; j++) {
        float displacement = tree::random(0.0f, 0.5f);

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
    this->setFixedRotation(false);

    this->addAngle(
        (direction ? m_rotationPower : -m_rotationPower)
    );

    this->setFixedRotation(true);
}

// Draw the player.
void tree::Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Draw engine particles.
    target.draw(engineParticles, states);

    addPhysicalTransform(states.transform);

    // Draw branches.
    for (auto branch : m_branches) {
        branch->draw(target, states);
    }

    target.draw(m_shape, states);
    target.draw(m_hat, states);
}
