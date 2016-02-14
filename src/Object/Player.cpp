#include <tree/Engine/Constant.hpp>
#include <tree/Math/Constant.hpp>
#include <tree/Math/Geometry.hpp>
#include <tree/Math/Random.hpp>
#include <tree/Math/Vector.hpp>
#include <tree/Object/Branch.hpp>
#include <tree/Object/Player.hpp>
#include <tree/Resource/Color.hpp>

// Constructor.
tree::Player::Player()
: tree::Lifeform::Lifeform(tree::Faction::wood, 10),
  engineParticles(200, 1500)
{
    m_thrustPower = 25E4;
    //m_rotationPower = 

    // Initialize shape.
    m_shape.setSize(tree::pixels(b2Vec2(2.0f, 1.0f)));
    m_shape.setFillColor(sf::Color::Green);

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
    this->setBody(bodyDef);

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
    this->addFixture(fixtureDef);

    // Test branch.
    rootBranch = new tree::branch::Wood();
}

// Destructor.
tree::Player::~Player()
{
    delete rootBranch;
}

// Act.
bool tree::Player::act(tree::Stage &stage)
{
    // Rotate player counter-clockwise.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        this->rotate(false);
    }

    // Rotate player clockwise.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        this->rotate(true);
    }
    
    // Thrust player.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->thrust(true);
    }

    // Apply space-brakes.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->thrust(false);
    }

    // Activate branches.
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        this->toggleShooting(true);
    } else {
        this->toggleShooting(false);
    }*/

    rootBranch->act(stage);
    return true;
}

// Toggles shooting.
void tree::Player::toggleShooting(bool isShooting)
{
}

// Perform a thrust.
void tree::Player::thrust(bool direction)
{
    this->applyThrust(direction);

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
                    0.001 * (direction ? -m_thrustPower : m_thrustPower)
                ),
                tree::paletteColor(palette::fire)
            );
        }
    }
}

// Draw the player.
void tree::Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Draw engine particles.
    target.draw(engineParticles, states);

    // Draw branches.
    addPhysicalTransform(states.transform);
    rootBranch->draw(target, states);

    // Draw player.
    target.draw(m_shape, states);
    target.draw(m_hat, states);
}
