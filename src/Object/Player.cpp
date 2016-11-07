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

    // Initialize shape.
    sf::Vector2f shapeSize(2.0f, 1.0f);

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

    // Initial molecule.
    ElementCollection elements;
    switch (tree::random(0, 2)) {
        case 0:
            elements.add(Element::Hydrogen, 1);
            break;

        case 1:
            elements.add(Element::Oxygen, 1);
            break;

        default:
            elements.add(Element::Hydrogen, 2);
            elements.add(Element::Oxygen, 1);
            break;
    }
    this->molecules.add(tree::generateMolecule(elements));
    this->generate();
}

// Destructor.
tree::Player::~Player()
{
    for (auto leaf : this->leaves) {
        delete leaf;
    }
}

// Generates the player based on its composition.
void tree::Player::generate()
{
    // Decide trunk color.
    sf::Color color;
    if (this->molecules[Molecule::Water]) {
        color = sf::Color(
            tree::random(10, 50),
            tree::random(0, 150),
            tree::random(150, 225)
        );
    }

    else if (this->molecules[Molecule::Oxygen]) {
        //m_shape.setOutlineThickness(1.0f);
        //color = sf::Color(200, 200, 200);
        //m_shape.setOutlineColor(color);
        color = sf::Color(25, 25, 25);
    }

    else {
        color = sf::Color(
            tree::random(150, 255),
            tree::random(150, 175),
            0
        );
    }

    // Give the trunk a shape.
    this->trunk.clear();
    this->trunk.setPrimitiveType(sf::TrianglesFan);
    Vector start(0.0f, 0.0f);
    Vector mid(7.0f, 1.5f);
    Vector end(0.0f, 3.0f);

    // Start the triangles fan.
    this->trunk.append(start.center(end));

    // Add arcs to the fan.
    tree::makeArc(this->trunk, start, mid, 0.4f, tree::NormalDistribution);
    tree::makeArc(this->trunk, mid,   end, -0.4f, tree::NormalDistribution);

    for (unsigned int i = 0; i < this->trunk.getVertexCount(); i++) {
        this->trunk[i].color = color;
    }

    for (auto leaf : this->leaves) {
        delete leaf;
    }
    this->leaves.clear();

    // Add leaves.
    unsigned int vertexIndex;
    for (auto moleculeCount : this->molecules) {
        for (unsigned int i = 0; i < moleculeCount.second; i++) {
            vertexIndex = tree::random(0, this->trunk.getVertexCount() - 1);

            this->leaves.push_back(
                new tree::Leaf(
                    this,
                    this->trunk[vertexIndex].position,
                    moleculeCount.first
                )
            );
        }
    }
}

// Sets the absorption target.
void tree::Player::setAbsorptionTarget(tree::Planet *planet)
{
    this->absorptionTarget = planet;
}


// Resets the absorption target.
void tree::Player::resetAbsorptionTarget()
{
    this->setAbsorptionTarget(nullptr);
    planetCrumbs.clear();
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
        this->absorptionTarget->crumble();

        tree::Vector position = this->absorptionTarget->getRandomPosition();
        tree::Vector velocity(
            this->getPosition().getAngle(position),
            100.0f
        );

        this->planetCrumbs.add(position, velocity, sf::Color::White);
    }
}

// Finalizes an absorption.
void tree::Player::takeAbsorptionTarget()
{
    this->molecules.add(this->absorptionTarget->getMolecules());
    this->resetAbsorptionTarget();
    this->generate();
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

    // Particle animations.
    planetCrumbs.animate(this->getPosition());
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
    // Draw particles.
    target.draw(engineParticles, states);
    target.draw(planetCrumbs, states);

    // Draw player.
    addPhysicalTransform(states.transform);
    target.draw(this->trunk, states);

    // Draw leaves.
    for (auto leaf : this->leaves) {
        leaf->draw(target, states);
    }
}
