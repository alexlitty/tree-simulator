#include <tree/Object/Weapon/Seed.hpp>

/**
 * Constructor.
 */

tree::weapon::Seed::Seed(Point initialPoint, Point initialVelocity)
: shape(0.4f, 6)
{
    this->shape.setFillColor(sf::Color::Yellow);
    Math::centerOrigin(this->shape);

    // Physical body.
    b2BodyDef body;
    body.position = initialPoint;
    body.type = b2_dynamicBody;
    body.fixedRotation = true;
    this->setBody(body);

    // Physical shape.
    b2PolygonShape pShape;
    pShape.SetAsBox(0.4f, 0.4f);

    // Physical fixture.
    b2FixtureDef fixture;
    fixture.shape = &pShape;
    fixture.density = 500.0f;
    fixture.friction = 0.05f;
    fixture.restitution = 1.0f;
    fixture.filter.categoryBits = tree::COLLISION_FRIEND;
    fixture.filter.maskBits = tree::COLLISION_WORLD | tree::COLLISION_ENEMY;
    this->addFixture(fixture);

    // Set initial velocity.
    this->setLinearVelocity(initialVelocity);
}

// Draws the seed.
void tree::weapon::Seed::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    this->addPhysicalTransform(states.transform);
    target.draw(this->shape, states);
}
