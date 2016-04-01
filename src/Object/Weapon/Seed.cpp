#include <tree/Object/Weapon/Seed.hpp>

/**
 * Constructor.
 */

tree::weapon::Seed::Seed(Point initialPoint, Point initialVelocity)
: shape(0.2f, 6)
{
    this->shape.setFillColor(sf::Color::Yellow);

    // Physical body.
    b2BodyDef body;
    body.position = initialPoint;
    body.type = b2_dynamicBody;
    body.fixedRotation = true;
    this->setBody(body);

    // Physical shape.
    b2PolygonShape pShape;
    pShape.SetAsBox(0.2f, 0.2f);

    // Physical fixture.
    b2FixtureDef fixture;
    fixture.shape = &pShape;
    fixture.density = 50.0f;
    fixture.friction = 0.05f;
    fixture.restitution = 1.0f;
    fixture.filter.categoryBits = tree::COLLISION_NORMAL;
    fixture.filter.maskBits = tree::COLLISION_WORLD;
    this->addFixture(fixture);

    // Set initial velocity.
    this->setLinearVelocity(initialVelocity);
}

// Draws the seed.
void tree::weapon::Seed::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    this->addPhysicalTransform(states.transform);
    target.draw(this->shape);
}
