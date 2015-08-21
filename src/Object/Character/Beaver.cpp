#include <tree/Math.hpp>
#include <tree/Object/Character/Beaver.hpp>

// Constructor.
tree::character::Beaver::Beaver(b2Vec2 position)
: tree::Lifeform::Lifeform(tree::Faction::beaver, 10)
{
    m_thrustPower = 1E4;

    // Initialize shape.
    m_tempShape.setSize(tree::pixels(b2Vec2(3.0f, 1.5f)));
    m_tempShape.setFillColor(sf::Color::Yellow);
    tree::Math::centerOrigin(m_tempShape);

    // Physical body.
    b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angularDamping = 0.0f;
    bodyDef.fixedRotation = true;
    this->setBody(bodyDef);

    // Physical shape.
    b2PolygonShape pShape;
    pShape.SetAsBox(1.5f, 0.75f);

    // Physical fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &pShape;
    fixtureDef.density = 100.0f;
    fixtureDef.friction = 0.05f;
    fixtureDef.restitution = 0.25;
    fixtureDef.filter.categoryBits = tree::COLLISION_WORLD;
    fixtureDef.filter.maskBits = -1;//tree::COLLISION_WORLD;
    this->addFixture(fixtureDef);
}

// Be a beaver.
bool tree::character::Beaver::act(tree::Objects &objects)
{
    b2Vec2 target(200.0f, 0.0f);
    this->moveBlindly(target);
    return true;
}

// Draw beaver.
void tree::character::Beaver::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    this->addPhysicalTransform(states.transform);
    target.draw(m_tempShape, states);
}
