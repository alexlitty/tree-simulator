#include <tree/Engine/Constant.hpp>
#include <tree/Math/Geometry.hpp>
#include <tree/Object/Planet.hpp>

// Constructor.
tree::Planet::Planet(float radius, float density, b2Vec2 position)
: m_shape(tree::pixels(radius), 60)
{
    this->createsGravity = true;

    // Drawn shape.
    m_shape.setFillColor(sf::Color::Red);
    Math::centerOrigin(m_shape);

    // Physics body.
    b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = false;
    setBody(bodyDef);

    // Physical shape.
    b2CircleShape pShape;
    pShape.m_radius = radius;

    // Physical fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &pShape;
    fixtureDef.density = density;
    fixtureDef.friction = 0.25f;
    fixtureDef.restitution = 0.25f;
    fixtureDef.filter.categoryBits = tree::COLLISION_WORLD;
    fixtureDef.filter.maskBits = -1;
    m_body->CreateFixture(&fixtureDef);
}

// Draw the planet.
void tree::Planet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    this->addPhysicalTransform(states.transform);
    target.draw(m_shape, states);
}
