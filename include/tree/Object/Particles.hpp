#ifndef TREESIMULATOR_OBJECT_PARTICLES_HPP
#define TREESIMULATOR_OBJECT_PARTICLES_HPP

#include <chrono>
#include <list>
#include <tree/Component/Drawable.hpp>
#include <tree/Physics/World.hpp>

namespace tree
{
    /**
     * Information about a single particle.
     *
     * Not drawable. Particle shapes are kept in a separated vertex array for better performance.
     */
    class Particle
    {
    public:

        // Birthtime of this particle.
        std::chrono::time_point<std::chrono::steady_clock> birthtime;

        // Physical body of this particle.
        b2Body *body;

        // Color of this particle.
        sf::Color color;
        
        /**
         * Constructor.
         */
        Particle(b2Body *initBody, sf::Color &initColor);

        /**
         * Destructor.
         */
        ~Particle();

        /**
         * Get the age of this particle in milliseconds.
         */
        unsigned int getAge() const;
    };

    /**
     * An isolated system of particles.
     *
     * Particles are automatically destroyed with time.
     */
    class Particles : public Drawable
    {
    protected:

        // Template to create new particles with.
        b2BodyDef m_bodyTemplate;

        // Template shape to create new particles with.
        b2PolygonShape m_shapeTemplate;

        // Template fixture to create new particles with.
        b2FixtureDef m_fixtureTemplate;

        // Maximum particle count.
        unsigned int m_max_count;

        // Maximum milliseconds a particle can live.
        unsigned int m_max_lifetime;

        // Particle objects.
        mutable std::list<Particle*> m_particles;

        // Particle shapes.
        mutable sf::VertexArray m_shapes;

        /**
         * Determine the transparency level of a particle.
         *
         * Based on particle age and lifetime remaining.
         */
        unsigned char getAlpha(unsigned int age) const;

    public:

        /**
         * Constructor.
         */
        Particles(int max_count, int lifetime = 250);

        /**
         * Destructor.
         */
        ~Particles();

        /**
         * Adds a new particle to the system.
         */
        void add(b2Vec2 position, b2Vec2 velocity, sf::Color color);

        /**
         * Removes the oldest particle from the system.
         */
        void pop() const;

        /**
         * Checks if the top particle needs culling.
         */
        bool needsCulling() const;

        /**
         * Draws the particle system.
         */
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}

#endif
