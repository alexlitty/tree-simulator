#include <tree/Math.hpp>
#include <tree/Object/NuggetLaser.hpp>

// Constructor.
tree::NuggetLaser::NuggetLaser(tree::Physical *parent)
: m_parent(parent),
  m_laser(sf::LinesStrip, 2)
{
    // Colorize laser.
    for (unsigned int i = 0; i < m_laser.getVertexCount(); i++) {
        m_laser[i].color = sf::Color::Red;
    }
}

// Swaps the laser target with a new one.
void tree::NuggetLaser::swapTarget(tree::Nuggetable *target)
{
    // Unmark old target.
    if (m_target) {
        m_target->markNuggetableTarget(false);
    }

    // Mark new target.
    m_target = target;
    if (m_target) {
        m_target->markNuggetableTarget(true);
    }
}

// Check the result of a physical ray cast.
float tree::NuggetLaser::ReportFixture(b2Fixture *fixture, const b2Vec2 &position, const b2Vec2 &normal, float fraction)
{
    void *object = fixture->GetBody()->GetUserData();

    // Cast to physical object.
    tree::Physical *physical =
        reinterpret_cast<tree::Physical*>(object);

    // Check if object can receive nuggets.
    if (!physical->isNuggetable()) {
        return -1;
    }

    // Cast to nuggetable object.
    tree::Nuggetable *nuggetable =
        dynamic_cast<tree::Nuggetable*>(
            physical
        );

    // Mark object as new target.
    m_goal = position;
    this->swapTarget(nuggetable);
    return fraction;
}

// Fires the laser.
void tree::NuggetLaser::fire(tree::nugget nugget)
{
    if (nugget == tree::nugget::invalid) {
        return;
    }

    if (m_cooldown.getElapsedTime().asSeconds() > 1.0f) {
        if (m_target) {
            m_cooldown.restart();
            m_target->receiveNugget(nugget);
        }
    }
}

// Act.
bool tree::NuggetLaser::act(tree::Stage &stage)
{
    // Loop through events.
    for (sf::Event event : stage.events) {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Q) {
                this->active = !this->active;
                if (!this->active) {
                    this->swapTarget(nullptr);
                }
            }
        }
    }

    // Laser actions.
    if (this->active) {

        // Reset laser target.
        this->swapTarget(nullptr);

        // Calculate and check laser path.
        b2Vec2 anchor = m_parent->getPosition();
        b2Vec2 goal = m_parent->getAngledPosition(100.0f);
        m_goal = goal;
        tree::world.RayCast(this, anchor, goal);

        // Update laser anchor.
        m_laser[0].position = tree::Math::vector(anchor);

        // Update laser target.
        m_laser[1].position = tree::Math::vector(m_goal);

        // Fire laser.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            this->fire(stage.nugget);
        }
    }
    return true;
}

// Draw.
void tree::NuggetLaser::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (this->active) {
        target.draw(m_laser, states);
    }
}
