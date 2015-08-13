#include <tree/Engine/Constant.hpp>
#include <tree/Math/Geometry.hpp>
#include <tree/Object/Planet.hpp>

// Constructor.
tree::Planet::Planet()
: m_shape(0.265f, 60)
{
    // Drawn shape.
    m_shape.setFillColor(sf::Color::Red);
    Math::centerOrigin(m_shape);
    m_shape.setPosition(1.0f, 0.0f);

    // Physics body.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = false;
    setBody(bodyDef);

    // Physical shape.
    b2CircleShape pShape;
    pShape.m_p.Set(1.0f, 0.0f);
    pShape.m_radius = 0.25f;

    // Physical fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &pShape;
    fixtureDef.density = 3.0E10;
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
