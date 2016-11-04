#include <tree/Math.hpp>
#include <tree/Object/Character/Beaver.hpp>

// Constructor.
tree::character::Beaver::Beaver(Players &_players, b2Vec2 position)
: tree::Lifeform::Lifeform(tree::Faction::beaver, 10),
  players(_players)
{
    m_thrustPower = 1E5;

    // Initialize shape.
    sf::Vector2f shapeSize(3.0f, 1.5f);
    m_tempShape.setSize(shapeSize);
    m_tempShape.setFillColor(sf::Color::Yellow);
    tree::centerOrigin(m_tempShape);

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
    fixtureDef.filter.maskBits = -1; //tree::COLLISION_WORLD;
    this->addFixture(fixtureDef);
}

// Handle collisions.
void tree::character::Beaver::onCollision(Physical *other)
{

}

// Be a beaver.
void tree::character::Beaver::act()
{
    // Find an enemy.
    tree::Physical *enemy = nullptr;
    for (auto lifeform : this->players) {
        if (this->isHostile(*lifeform)) {
            enemy = lifeform;
            break;
        }
    }

    // Move toward enemy.
    if (enemy != nullptr) {
        Vector position = enemy->getPosition();
        this->moveBlindly(position);
    }

    // Find a planet.
    /*tree::Physical *planet = sta!ge.gravities[0];
    this->maintainDistance(planet->getPosition(), 200.0f);
    return true;*/
}

// Draw beaver.
void tree::character::Beaver::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Color color;

    if (isThrusting()) {
        color = sf::Color::Yellow;
    } else {
        color.r = color.g = color.b = 175;
    }
    m_tempShape.setFillColor(color);

    this->addPhysicalTransform(states.transform);
    target.draw(m_tempShape, states);
}
