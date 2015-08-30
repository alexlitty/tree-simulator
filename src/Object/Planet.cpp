#include <tree/Engine/Constant.hpp>
#include <tree/Math/Geometry.hpp>
#include <tree/Object/Planet.hpp>
#include <tree/Resource/Color.hpp>
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
    fixtureDef.friction = 0.25f;
    fixtureDef.restitution = 0.25f;
    fixtureDef.filter.categoryBits = tree::COLLISION_WORLD;
    fixtureDef.filter.maskBits = -1;
    m_fixture = this->addFixture(fixtureDef);
}

// Constructor, with initial nugget.
tree::Planet::Planet(b2Vec2 position, tree::nugget initialNugget)
: tree::Planet::Planet(position)
{
    m_nuggets.add(initialNugget);
    this->generate();
}

// Destructor.
tree::Planet::~Planet()
{
    delete m_texture;
}

// Gets the radius of this planet.
float tree::Planet::getRadius() const
{
    return m_nuggets.total() * 1.0f;
}

// Gets the density of this planet.
float tree::Planet::getNuggetDensity() const
{
    return m_nuggets.total() * 3E7;
}

// Generates this planet.
#include <iostream>
void tree::Planet::generate()
{
    float radius = this->getRadius();

    // Update physical shape.
    m_fixture->GetShape()->m_radius = radius;
    m_fixture->SetDensity(this->getNuggetDensity());
    this->updateMass();

    // Update visual shape.
    m_shape.setRadius(radius);
    Math::centerOrigin(m_shape);

    // Reset texture.
    unsigned int textureSize = tree::nextPot(
        static_cast<unsigned int>(radius * 16)
    );
    delete m_texture;
    m_texture = new sf::RenderTexture;
    m_texture->create(textureSize, textureSize);

    // Set new texture view.
    sf::View view(sf::FloatRect(0, 0, textureSize, textureSize));
    m_texture->setView(view);

    // Generate planet, based on nugget composition.
    m_texture->setSmooth(true);
    m_texture->clear(
        tree::nuggetColor(m_nuggets.list[0].type)
    );
    for (auto comp : m_nuggets.list) {
        tree::brush::palette = tree::nuggetPalette(comp.type);
        tree::brush::spots(m_texture, 120, 10.0f, 20.0f);
    }
    m_texture->display();

    // Apply new texture to shape.
    m_shape.setTexture(&m_texture->getTexture(), true);
}

// Draw the planet.
void tree::Planet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    this->addPhysicalTransform(states.transform);
    target.draw(m_shape, states);
}
