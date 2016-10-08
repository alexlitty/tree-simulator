#include <tree/Engine/Constant.hpp>
#include <tree/Math.hpp>
#include <tree/Object/Planet.hpp>
#include <tree/Resource/Color.hpp>
#include <tree/Resource/Shader.hpp>
#include <tree/Utility/Brush.hpp>

// Main constructor.
tree::Planet::Planet(b2Vec2 position)
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

    // Visual shape.
    m_shape.setPointCount(60);
    m_shape.setRadius(1.0f);

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
    delete m_texture;
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

    // Update visual shape.
    m_shape.setRadius(radius);
    m_shape.setPointCount(
        (std::floor(radius / 30) + 1) * 60
    );
    tree::centerOrigin(m_shape);

    // Calculate new texture size.
    unsigned int textureSize = tree::nextPowerOfTwo(
        static_cast<unsigned int>(radius)
    );

    // New texture required.
    if (!m_texture || textureSize != m_texture->getSize().x) {

        // Delete old texture, create new texture.
        delete m_texture;
        m_texture = new sf::RenderTexture;
        m_texture->create(textureSize, textureSize);
        m_texture->setSmooth(false);

        // Set new texture view.
        m_texture->setView(
            sf::View(
                sf::FloatRect(0, 0, textureSize, textureSize)
            )
        );
    }

    // Clear texture.
    m_texture->clear();
    //tree::brush::palette = tree::nuggetPalette(nuggets.list[0].type);
    //tree::brush::noise(m_texture);

    /*
    for (auto &kv : nuggets.list) {
        tree::brush::palette = tree::nuggetPalette(comp.type);
        tree::brush::spots(
            m_texture,
            120,
            textureSize / 3,
            textureSize / 2
        );
    }
    */
    m_texture->display();

    // Apply new texture to shape.
    m_shape.setTexture(&m_texture->getTexture(), true);

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
    return tree::randomPointOnCircle(m_shape.getRadius(), this->getPosition());
}

// Draw the planet.
void tree::Planet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    this->addPhysicalTransform(states.transform);

    // Draw planet.
    states.shader = &tree::Shader::Fisheye;
    target.draw(m_shape, states);
}
