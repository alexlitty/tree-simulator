#include <tree/Engine/Constant.hpp>
#include <tree/Math/Vector.hpp>
#include <tree/Object/Particles.hpp>

// Particle constructor.
tree::Particle::Particle(b2BodyDef &bodyDef, sf::Color &initColor)
: color(initColor)
{
    setBody(bodyDef);
    birthtime = std::chrono::steady_clock::now();
}

// Get the age of this particle in milliseconds.
unsigned int tree::Particle::getAge() const
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - this->birthtime
    ).count();
}

// Determine the transparency level of a particle.
unsigned char tree::Particles::getAlpha(unsigned int age) const
{
    static const float particle_cap = 0.00f;

    if (age > m_max_lifetime) {
        return 0;
    }

    float percentage = (1.0f * age) / m_max_lifetime;
    if (percentage < particle_cap) {
        return 255;
    }
    else {
        float modifier = (percentage - particle_cap) / (1.0f - particle_cap);
        if (modifier < 0) {
            return 0;
        } else {
            return 255 - (modifier * 255);
        }
    }
}

// Particle system constructor.
tree::Particles::Particles(int max_count, int lifetime)
: m_max_count(max_count),
  m_max_lifetime(lifetime),
  m_shapes(sf::Points, 0)
{
    m_bodyTemplate.type = b2_dynamicBody;
    m_shapeTemplate.SetAsBox(1.0f, 1.0f);
    m_fixtureTemplate.shape = &m_shapeTemplate;
    m_fixtureTemplate.density = 0.0001f;
    m_fixtureTemplate.friction = 0.0f;
    m_fixtureTemplate.restitution = 1.0f;
    m_fixtureTemplate.filter.categoryBits = tree::COLLISION_PARTICLES;
    m_fixtureTemplate.filter.maskBits = tree::COLLISION_WORLD;
}

// Particle system destructor.
tree::Particles::~Particles()
{
    for (unsigned int i = 0; i < m_particles.size(); i++) {
        this->pop();
    }
}

// Adds a new particle to the system.
void tree::Particles::add(b2Vec2 position, b2Vec2 velocity, sf::Color color)
{
    // Prevent particle overflow.
    if (m_particles.size() >= m_max_count) {
        this->pop();
    }

    // Create and add new particle.
    m_bodyTemplate.position = position;
    Particle *particle = new Particle(m_bodyTemplate, color);
    particle->addFixture(m_fixtureTemplate);
    particle->setLinearVelocity(velocity);
    m_particles.push_back(particle);

    // Add drawing shape.
    if (m_shapes.getVertexCount() < m_max_count) {
        m_shapes.append(sf::Vertex());
    }
}

// Removes the oldest particle from the system.
void tree::Particles::pop() const
{
    Particle *particle = m_particles.front();
    delete particle;
    m_particles.pop_front();
}

// Checks if the top particle needs culling.
bool tree::Particles::needsCulling() const
{
    // Check if particles exist.
    if (m_particles.empty()) {
        return false;
    }

    // Decide if top particle is too old.
    return (m_particles.front()->getAge() > m_max_lifetime);
}

// Draws the particle system.
void tree::Particles::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Cull old particles.
    while (this->needsCulling()) {
        this->pop();
    }

    // Draw if particles exist.
    if (!m_particles.empty()) {

        // Copy particle information to drawing shapes.
        unsigned int i = 0;
        for (auto particle : m_particles) {

            // Copy information.
            m_shapes[i].position = particle->getPixelPosition();
            m_shapes[i].color = particle->color;
            m_shapes[i].color.a = this->getAlpha(particle->getAge());
            i++;
        }

        // Hide inactive particle shapes.
        while (i < m_shapes.getVertexCount()) {
            m_shapes[i].color.a = 0;
            i++;
        }

        // Draw particles.
        target.draw(m_shapes, states);
    }
}
