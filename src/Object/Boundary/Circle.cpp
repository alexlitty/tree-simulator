#include <tree/Math.hpp>
#include <tree/Object/Boundary/Circle.hpp>

tree::boundary::Circle::Circle(float radius)
{
    Angle angle;
    Vector currentVector, previousVector;

    // Physical body definition.
    b2BodyDef bodyDef;
    bodyDef.position.Set(0.0f, 0.0f);
    bodyDef.type = b2_staticBody;
    this->setBody(bodyDef);

    // Add circular edge fixtures.
    for (unsigned int i = 0; i < 180; i++) {
        previousVector = Vector(angle, radius);

        angle.degrees(angle.degrees() + 2.0f);
        currentVector = Vector(angle, radius);

        b2EdgeShape edge;
        edge.Set(previousVector, currentVector);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &edge;
        this->addFixture(fixtureDef);
    }

    // Prepare drawn shape.
    this->shape.setRadius(radius);
    this->shape.setPointCount(180);
    tree::centerOrigin(this->shape);

    this->shape.setPosition(0.0f, 0.0f);
    this->shape.setFillColor(sf::Color::Transparent);

    this->shape.setOutlineThickness(1000.0f);
    this->shape.setOutlineColor(sf::Color(175, 75, 75));
}

void tree::boundary::Circle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->shape, states);
}
