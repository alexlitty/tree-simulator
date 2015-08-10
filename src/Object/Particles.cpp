#include <tree/Engine/Constant.hpp>
#include <tree/Math/Vector.hpp>
#include <tree/Object/Particles.hpp>

// Constructor.
tree::Particles::Particles(int max)
: m_max(max),
  m_shapes(sf::Points, 0)
{
    m_bodyTemplate.type = b2_dynamicBody;
    m_shapeTemplate.SetAsBox(0.01f, 0.01f);
    m_fixtureTemplate.shape = &m_shapeTemplate;
    m_fixtureTemplate.density = 1.0f;
    m_fixtureTemplate.friction = 0.0f;
    m_fixtureTemplate.filter.categoryBits = tree::COLLISION_PARTICLES;
    m_fixtureTemplate.filter.maskBits = tree::COLLISION_WORLD;
}

// Destructor.
tree::Particles::~Particles()
{
    for (unsigned int i = 0; i < m_bodies.size(); i++) {
        tree::Physics::world.DestroyBody(m_bodies[i]);
    }
}

// Adds a new particle to the system.
void tree::Particles::add(b2Vec2 position, b2Vec2 velocity)
{
    if (m_bodies.size() >= m_max) {
        b2Body *temp = m_bodies[0];
        tree::Physics::world.DestroyBody(temp);
        m_bodies.erase(m_bodies.begin());
    }

    m_bodyTemplate.position = position;
    b2Body *body = tree::Physics::world.CreateBody(&m_bodyTemplate);
    body->CreateFixture(&m_fixtureTemplate);
    body->SetLinearVelocity(velocity);
    m_bodies.push_back(body);

    if (m_shapes.getVertexCount() < m_max) {
        m_shapes.append(
            sf::Vertex(
                tree::Math::vector(position),
                sf::Color::Green
            )
        );
    }
}

// Draws the particle system.
void tree::Particles::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (unsigned int i = 0; i < m_bodies.size(); i++) {
        m_shapes[i].position = tree::Math::vector(m_bodies[i]->GetPosition());
    }

    target.draw(m_shapes, states);
}
