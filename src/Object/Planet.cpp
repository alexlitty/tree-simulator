#include <tree/Engine/Constant.hpp>
#include <tree/Math.hpp>
#include <tree/Object/Planet.hpp>
#include <tree/Resource/Color.hpp>
#include <tree/Resource/Shader.hpp>
#include <tree/Brush.hpp>
#include <tree/Sprite/Planets/Sun.hpp>
#include <tree/Sprite/Planets/Oxygen.hpp>
#include <tree/Sprite/Planets/Water.hpp>

// Main constructor.
tree::Planet::Planet(b2Vec2 position)
: sprite(nullptr)
{
    this->createsGravity = true;

    // Physics body.
    b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = false;
    setBody(bodyDef);

    // Physical shape.
    b2CircleShape pShape;
    pShape.m_radius = 1.0f;

    // Physical fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &pShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.85f;
    fixtureDef.restitution = 0.25f;
    fixtureDef.filter.categoryBits = tree::COLLISION_WORLD;
    fixtureDef.filter.maskBits = -1;
    m_fixture = this->addFixture(fixtureDef);
}

// Destructor.
tree::Planet::~Planet()
{
    delete this->sprite;
}

// Get the molecules that compose this planet.
tree::MoleculeCollection& tree::Planet::getMolecules()
{
    return this->molecules;
}

// Gets the radius of this planet.
float tree::Planet::getRadius() const
{
    return this->molecules.count() * 1.0f;
}

// Gets the density of this planet.
float tree::Planet::getMoleculeDensity() const
{
    return 3E4 * this->molecules.count();
}

// Receives a new set of molecules.
void tree::Planet::receiveMolecules(tree::MoleculeCollection newMolecules)
{
    this->molecules.add(newMolecules);
    this->generate();
}

// Generates this planet based on molecule composition.
void tree::Planet::generate()
{
    float radius = this->getRadius();

    // Update physical shape.
    m_fixture->GetShape()->m_radius = radius;
    m_fixture->SetDensity(this->getMoleculeDensity());
    this->updateMass();

    // Update physical settings.
    m_torquePower = 3E15;

    // Update sprite.
    if (this->sprite) {
        delete this->sprite;
    }

    if (this->molecules["water"]) {
        this->sprite = new tree::sprite::WaterPlanet(radius);
    }

    else if (this->molecules["oxygen"]) {
        this->sprite = new tree::sprite::OxygenPlanet(radius);
    }

    else {
        this->sprite = new tree::sprite::Sun(radius);
    }

    // Initialize health.
    this->restoreHealth();
}

// Check if the planet can crumble further.
bool tree::Planet::canCrumble() const
{
    return this->health > 0;
}

// Crumble away from absorption.
void tree::Planet::crumble()
{
    if (this->canCrumble()) {
        this->health--;
    }
}

// Restores any damage from crumbling.
void tree::Planet::restoreHealth()
{
    this->health = this->molecules.count() * 5;
}

// Gets a random position on this planet.
tree::Vector tree::Planet::getRandomPosition() const
{
    return tree::randomPointOnCircle(this->getRadius(), this->getPosition());
}

// Perform actions over time.
void tree::Planet::act()
{
    this->sprite->animate();
}

// Draw the planet.
void tree::Planet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    this->addPhysicalTransform(states.transform);

    // Draw planet.
    this->sprite->draw(target, states);
}
