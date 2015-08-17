#include <tree/Engine/Constant.hpp>
#include <tree/Math.hpp>
#include <tree/Object/Branch/Birch.hpp>
#include <tree/Resource/Color.hpp>

#include <iostream>

// Birch leaf constructor.
tree::branches::BirchLeaf::BirchLeaf(b2Vec2 position, float angle, b2Vec2 velocity)
: m_triangle(sf::Triangles, 0)
{
    angle += tree::Math::PI / 2;

    // Drawn shape.
    sf::Vertex vertex;
    vertex.color = sf::Color::Blue;
    vertex.position = sf::Vector2f(0.0f, -0.75f);
    m_triangle.append(vertex);

    vertex.position = sf::Vector2f(-0.75f, 0.0f);
    m_triangle.append(vertex);

    vertex.position = sf::Vector2f(0.75f, 0.0f);
    m_triangle.append(vertex);

    m_center = tree::Math::getCenter(m_triangle);
    m_center.x *= 2;
    m_center.y *= 2;

    // Physical body.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position;
    bodyDef.linearVelocity = velocity;
    bodyDef.fixedRotation = true;
    this->setBody(bodyDef);

    // Physical shape.
    b2Vec2 vertices[3];
    b2PolygonShape shape;
    for (unsigned int i = 0; i < 3; i++) {
        vertices[i] = tree::Math::vector(
            m_triangle[i].position
        );
    }
    shape.Set(vertices, 3);

    // Physical fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 100.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 1.0f;
    fixtureDef.filter.categoryBits = tree::COLLISION_NORMAL;
    fixtureDef.filter.maskBits = tree::COLLISION_WORLD;
    this->addFixture(fixtureDef);
    this->setAngle(angle);
}

// Draw birch leaf.
void tree::branches::BirchLeaf::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    this->addPhysicalTransform(states.transform);
    states.transform.translate(-m_center);
    target.draw(m_triangle, states);
}

// Branch constructor.
tree::branches::Birch::Birch(Physical *parent, b2Vec2 position, b2Vec2 anchor)
: m_parent(parent),
  m_position(position),
  m_anchor(anchor),
  m_tempShape(tree::pixels(0.5f), 60),
  m_branchShape(sf::Lines, 2)
{
    // Node shape.
    b2CircleShape pShape;
    pShape.m_radius = 0.5f;
    pShape.m_p = position;

    // Node fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &pShape;
    fixtureDef.density = 10.0f;
    fixtureDef.friction = 0.50f;
    fixtureDef.restitution = 0.25f;
    fixtureDef.filter.categoryBits = tree::COLLISION_NORMAL;
    fixtureDef.filter.maskBits = tree::COLLISION_WORLD;
    b2Fixture *fixture = parent->addFixture(fixtureDef);
    this->fixtures.push_back(fixture);

    // Node visual.
    m_tempShape.setFillColor(sf::Color::Green);
    Math::centerOrigin(m_tempShape);
    m_tempShape.setPosition(tree::Math::vector(position));

    // Branch shape.
    b2EdgeShape branchShape;
    branchShape.Set(position, anchor);

    // Branch fixture.
    fixtureDef.shape = &branchShape;
    fixture = parent->addFixture(fixtureDef);
    this->fixtures.push_back(fixture);

    // Branch visual.
    sf::Vertex vertex;
    vertex.color = sf::Color::Magenta;
    vertex.position = tree::Math::vector(position);
    m_branchShape.append(vertex);

    vertex.position = tree::Math::vector(anchor);
    m_branchShape.append(vertex);
}

// Shoot leaves.
bool tree::branches::Birch::act(tree::Objects &objects)
{
    // Check if it's time to shoot.
    if (m_activated) {
        if (m_clock.getElapsedTime().asMilliseconds() > 75) {

            // Create new leaf.
            objects.push_back(
                new BirchLeaf(
                    m_parent->getPosition(),
                    /*tree::Math::createVector(
                        m_parent->getAngle()
                            + tree::Math::getAngle(m_position),
                        tree::Math::magnitude(m_position)
                    ),*/
                    /*m_parent->getAngledPosition(0.5f)
                    tree::Math::createVector(
                        m_parent->getAngle(),
                        tree::Math::magnitude(m_position)
                    ),*/
                    m_parent->getAngle(),
                    m_parent->getLinearVelocity() + m_parent->getAngledPosition(500.0f) + m_position
                )
            );

            // Restart shooting timer.
            m_clock.restart();
        }
    }

    return true;
}

// Draw branch.
void tree::branches::Birch::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw branch.
    target.draw(m_branchShape, states);

    // Draw node.
    target.draw(m_tempShape, states);
}
