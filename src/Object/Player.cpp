#include <tree/Engine/Constant.hpp>
#include <tree/Math.hpp>
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
    sf::Vector2f shapeSize(2.0f, 1.0f);
    m_shape.setSize(shapeSize);
    m_shape.setFillColor(sf::Color::Green);

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
    fixtureDef.filter.categoryBits = tree::COLLISION_FRIEND;
    fixtureDef.filter.maskBits = tree::COLLISION_WORLD | tree::COLLISION_ENEMY;
    this->addFixture(fixtureDef);

    // Add first leaf.
    this->addLeaf();
}

// Destructor.
tree::Player::~Player()
{
    for (auto leaf : this->leaves) {
        delete leaf;
    }

    this->destroyCrumbs();
}

// Destroys nugget crumbs.
void tree::Player::destroyCrumbs()
{
    for (auto crumb : this->crumbs) {
        delete crumb;
    }
    this->crumbs.clear();
}

// Attracts nugget crumbs.
void tree::Player::attractCrumbs()
{
    for (auto crumb : this->crumbs) {
        crumb->moveToward(this->getPosition());
    }
}

// Adds a leaf to the player.
void tree::Player::addLeaf()
{
    tree::Leaf* leaf = new tree::Leaf(this);
    leaf->position.x = 1.5f;
    leaf->position.y = 0.0f;

    this->leaves.push_back(leaf);
}

// Sets the absorption target.
void tree::Player::setAbsorptionTarget(tree::Planet *planet)
{
    this->absorptionTarget = planet;
}


// Resets the absorption target.
void tree::Player::resetAbsorptionTarget()
{
    this->absorptionTarget->uncrumble();
    this->setAbsorptionTarget(nullptr);
}

// Gets the absorption target.
tree::Planet* tree::Player::getAbsorptionTarget() const
{
    return this->absorptionTarget;
}

// Checks whether the tree is absorbing something.
bool tree::Player::isAbsorbing() const
{
    return this->absorptionTarget != nullptr;
}

// Absorbs from the currently targeted planet.
void tree::Player::absorb()
{
    if (this->isAbsorbing()) {
        this->absorptionTarget->crumble(this->crumbs);
    }
}

// Checks whether the brake is engaged.
bool tree::Player::isBrakeEngaged() const
{
    return this->isAbsorbing();
}

// Act.
void tree::Player::act(std::vector<tree::weapon::Seed*> &seeds)
{
    // Move the player.
    bool moving = false;
    Angle goal;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        moving = true;
        goal.degrees(0);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        moving = true;
        goal.degrees(90);
    }
    
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        moving = true;
        goal.degrees(180);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        moving = true;
        goal.degrees(270);
    }

    else {
        moving = false;
        goal = this->getAngle();
    }

    // Rotate toward goal direction.
    Angle deltaAngle = goal - this->getAngle();
    deltaAngle.radians(deltaAngle.radians() / 3);

    this->rotate(deltaAngle);

    // Engage brakes.
    if (this->isBrakeEngaged()) {
        tree::Vector brakingVelocity = this->getLinearVelocity();
        brakingVelocity *= 0.875f;
        this->setLinearVelocity(brakingVelocity);
    }

    // Thrust.
    else {
        if (moving) {
            this->thrust(true);
        }
    }

    // Activate leaves.
    bool shooting = false;
    Angle angle;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        shooting = true;
        angle.degrees(270);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        shooting = true;
        angle.degrees(0);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        shooting = true;
        angle.degrees(90);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        shooting = true;
        angle.degrees(180);
    }

    if (shooting) {
        for (auto leaf : this->leaves) {
            leaf->shoot(seeds, angle);
        }
    }

    this->attractCrumbs();
}

// Perform a thrust.
void tree::Player::thrust(bool direction)
{
    this->applyThrust(direction);

    Vector baseEngineVector(this->getAngle(), 0.1f);
    baseEngineVector = this->getPosition() - baseEngineVector;

    for (unsigned int j = 0; j < 2; j++) {
        float displacement = tree::random(0.0f, 0.5f);

        for (unsigned int i = 0; i < 2; i++) {

            // Calculate engine angle.
            Angle engineAngle;
            engineAngle.radians(
                m_body->GetAngle() - (PI / 2)
            );

            // Create engine vector.
            Vector engineVector(
                engineAngle,
                (i == 0) ? -displacement : displacement
            );
            engineVector = baseEngineVector - engineVector;

            // Calculate particle angle.
            Angle particleAngle;
            particleAngle.radians(
                (((i == 0) ? 1 : -1) * tree::random(-0.5f, 0.785f))
            );

            // Create particle vector.
            Vector particleVector(
                this->getAngle() + particleAngle,
                0.001 * (direction ? -m_thrustPower : m_thrustPower)
            );

            // Create particle.
            engineParticles.add(
                engineVector,
                particleVector,
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

    // Draw crumbs.
    for (auto crumb : this->crumbs) {
        target.draw(*crumb, states);
    }

    // Draw player.
    addPhysicalTransform(states.transform);
    target.draw(m_shape, states);

    // Draw leaves.
    for (auto leaf : this->leaves) {
        target.draw(*leaf, states);
    }
}
