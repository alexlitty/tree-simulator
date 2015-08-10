#ifndef TREESIMULATOR_OBJECT_PARTICLES_HPP
#define TREESIMULATOR_OBJECT_PARTICLES_HPP

#include <tree/Component/Drawable.hpp>
#include <tree/Physics/World.hpp>

namespace tree
{
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
        unsigned int m_max;

        // Current particles.
        std::vector<b2Body*> m_bodies;

        // Particle shapes.
        mutable sf::VertexArray m_shapes;

    public:

        /**
         * Constructor.
         */
        Particles(int max);

        /**
         * Destructor.
         */
        ~Particles();

        /**
         * Adds a new particle to the system.
         */
        void add(b2Vec2 position, b2Vec2 velocity);

        /**
         * Draws the particle system.
         */
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}

#endif
