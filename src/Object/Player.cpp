#include <tree/Engine/Constant.hpp>
#include <tree/Math.hpp>
#include <tree/Object/Player.hpp>
#include <tree/Resource/Color.hpp>

// Constructor.
tree::Player::Player()
: tree::Lifeform::Lifeform(tree::Faction::wood),
  engineParticles(200, 1500)
{
    m_thrustPower = 25E4;
    this->setMaxDamage(100);

    // Initialize shape.
    sf::Vector2f shapeSize(2.0f, 1.0f);

    // Physical body definition.
    b2BodyDef bodyDef;
    bodyDef.position.Set(1.0f, 1.0f);
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
    switch (tree::random(0, 2)) {
        case 0:
            this->elements.add(Element::Hydrogen, 1);
            break;

        case 1:
            this->elements.add(Element::Oxygen, 1);
            break;

        default:
            this->elements.add(Element::Hydrogen, 2);
            this->elements.add(Element::Oxygen, 1);
            break;
    }
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
    // Decide color schemes.
    sf::Color woodColor(222, 184, 135);
    sf::Color color;

    // Turn elements into molecules.
    ElementCollection generatingElements = this->elements;
    this->molecules.clear();
    while (!generatingElements.isEmpty()) {
        this->molecules.add(tree::generateMolecule(generatingElements));
    }

    if (this->molecules[Molecule::Water]) {
        color = tree::getRandomColor(Molecule::Water);
    }

    else if (this->molecules[Molecule::Oxygen]) {
        color = tree::getRandomColor(Molecule::Oxygen);
    }

    else {
        color = tree::getRandomColor(Molecule::Hydrogen);
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
    tree::makeArc(this->trunk, start, mid, -0.2f, tree::NormalDistribution);
    unsigned int tipIndex = this->trunk.getVertexCount() - 1;
    tree::makeArc(this->trunk, mid,   end, -0.2f, tree::NormalDistribution);

    unsigned int trunkVertexCount = this->trunk.getVertexCount();
    for (unsigned int i = 0; i < trunkVertexCount; i++) {
        this->trunk[i].color = woodColor;
    }

    // Add decorative branches.
    this->branches.clear();
    this->decorativeLeaves.clear();
    for (unsigned int i = 0; i < 2; i++) {
        int sign = i == 0 ? -1 : 1;

        unsigned int branchCenterIndex = tipIndex + ((tipIndex / 2) * sign);
        start = this->trunk[branchCenterIndex - 3].position;
        end = this->trunk[branchCenterIndex + 2].position;
        mid = Vector(
            start.x + tree::random(4, 6),
            start.y + (tree::random(2, 6) * (i == 0 ? -1 : 1))
        );

        sf::VertexArray branch;
        branch.setPrimitiveType(sf::TrianglesFan);
        branch.append(start.center(end));
        tree::makeArc(branch, start, mid, -1.0f * sign, tree::NormalDistribution);
        tree::makeArc(branch, mid, end, 1.0f * sign, tree::NormalDistribution);

        for (unsigned int i = 0; i < branch.getVertexCount(); i++) {
            branch[i].color = woodColor;
        }
        this->branches.push_back(branch);

        // Decorative leaves.
        sf::CircleShape decorativeLeafShape(5.0f, 20);
        tree::centerOrigin(decorativeLeafShape);
        decorativeLeafShape.setPosition(mid);
        decorativeLeafShape.setFillColor(color);
        this->decorativeLeaves.push_back(decorativeLeafShape);
    }

    // Destroy existing leaves.
    for (auto leaf : this->leaves) {
        delete leaf;
    }
    this->leaves.clear();

    // Generate new leaves.
    unsigned int leavesCount;
    for (auto moleculeCount : this->molecules) {
        leavesCount = moleculeCount.second / 15;
        if (!leavesCount && moleculeCount.second) {
            leavesCount = 1;
        }

        // No decorative leaves? No leaves.
        if (!this->decorativeLeaves.size()) {
            break;
        }

        for (unsigned int i = 0; i < leavesCount; i++) {
            this->leaves.push_back(
                new tree::Leaf(
                    this,
                    tree::randomPointOnCircle(
                        this->decorativeLeaves[
                            tree::random(0, this->decorativeLeaves.size() - 1)
                        ]
                    ),
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
    ElementCollection absorbedElements = this->absorptionTarget->getElements();
    this->elements.add(absorbedElements);
    this->resetAbsorptionTarget();
    this->generate();
}

// Checks whether the brake is engaged.
bool tree::Player::isBrakeEngaged() const
{
    return this->isAbsorbing();
}

// Act.
void tree::Player::act(std::vector<tree::Lifeform*> &enemies, std::vector<tree::Weapon*> &weapons)
{
    // Move the player.
    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

    if (down && right) {
        this->targetAngle.radians(QUARTER_PI);
    }

    else if (down && left) {
        this->targetAngle.radians(THREE_QUARTERS_PI);
    }

    else if (up && left) {
        this->targetAngle.radians(FIVE_QUARTERS_PI);
    }

    else  if (up && right) {
        this->targetAngle.radians(SEVEN_QUARTERS_PI);
    }

    else if (right) {
        this->targetAngle.radians(0.0f);
    }

    else if (down) {
        this->targetAngle.radians(HALF_PI);
    }

    else if (left) {
        this->targetAngle.radians(PI);
    }

    else if (up) {
        this->targetAngle.radians(THREE_HALVES_PI);
    }

    // Rotate toward goal direction.
    Angle deltaAngle;
    if (this->getAngle() != this->targetAngle) {
        Angle incrementAngle;
        incrementAngle.radians(tree::PI / 3);

        Angle newAngle = this->getAngle();
        newAngle.ease(this->targetAngle, incrementAngle);
        this->setAngle(newAngle);

        // Burst into new direction.
        if (newAngle == this->targetAngle) {
            this->setLinearVelocity(Vector(this->targetAngle, this->getLinearVelocity().getMagnitude()));
        }
    }


    // Engage absolute brakes.
    if (this->isBrakeEngaged() || (!up && !left && !down && !right)) {
        tree::Vector brakingVelocity = this->getLinearVelocity();
        brakingVelocity *= 0.875f;
        this->setLinearVelocity(brakingVelocity);
    }

    // Thrust.
    else if (up || left || down || right) {
        this->thrust(true);
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

    for (auto leaf : this->leaves) {
        leaf->act();
        if (shooting) {
            leaf->shoot(angle, enemies, weapons);
        }
    }

    // Particle animations.
    planetCrumbs.animate(this->getPosition());
}

// Perform a thrust.
void tree::Player::thrust(bool direction)
{
    if (this->getLinearVelocity().getMagnitude() < 500.0f) {
        this->applyThrust(direction);
    }

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
    for (auto decorativeLeaf : this->decorativeLeaves) {
        target.draw(decorativeLeaf, states);
    }
    for (auto branch : this->branches) {
        target.draw(branch, states);
    }

    // Draw leaves.
    for (auto leaf : this->leaves) {
        leaf->draw(target, states);
    }
}
