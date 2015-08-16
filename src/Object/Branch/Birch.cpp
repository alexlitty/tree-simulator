#include <tree/Engine/Constant.hpp>
#include <tree/Math/Geometry.hpp>
#include <tree/Math/Vector.hpp>
#include <tree/Object/Branch/Birch.hpp>
#include <tree/Resource/Color.hpp>

// Draw birch leaf.
void tree::branches::BirchLeaf::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::VertexArray temp;
    temp.setPrimitiveType(sf::Triangles);

    sf::Vertex test(
        tree::Math::vector(this->getPosition()),
        tree::paletteColor(tree::palette::random)
    );

    temp.append(test);

    target.draw(temp, states);
}

// Branch constructor.
tree::branches::Birch::Birch(b2Body *parent, b2Vec2 position, b2Vec2 anchor)
: m_tempShape(tree::pixels(0.5f), 60),
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
    b2Fixture *fixture = parent->CreateFixture(&fixtureDef);
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
    fixture = parent->CreateFixture(&fixtureDef);
    this->fixtures.push_back(fixture);

    // Branch visual.
    sf::Vertex vertex;
    vertex.color = sf::Color::Magenta;
    vertex.position = tree::Math::vector(position);
    m_branchShape.append(vertex);

    vertex.position = tree::Math::vector(anchor);
    m_branchShape.append(vertex);
}

// Upkeep leaves.
void tree::branches::Birch::act()
{

}

// Draw branch and leaves.
void tree::branches::Birch::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw branch.
    target.draw(m_branchShape, states);

    // Draw node.
    target.draw(m_tempShape, states);

    // Draw leaves.
    for (auto &leaf : m_leaves) {
        leaf.draw(target, states);
    }
}
