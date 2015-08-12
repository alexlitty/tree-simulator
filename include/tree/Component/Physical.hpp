#ifndef TREESIMULATOR_COMPONENT_PHYSICAL_HPP
#define TREESIMULATOR_COMPONENT_PHYSICAL_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <tree/Physics/World.hpp>

namespace tree
{
    /**
     * A physical object in the game world.
     *
     * Physics powered by Box2D.
     */
    class Physical
    {
    protected:

        // Physical body.
        b2Body *m_body;

        /**
         * Create a body and add it to the physics system.
         *
         * Automatically destroys body upon class destruction.
         */
        void setBody(b2BodyDef &bodyDef);

        /**
         * Deletes the current body and removes it from the physics system.
         */
        void deleteBody();

    public:

        /**
         * Constructor.
         */
        Physical();

        /**
         * Destructor.
         */
        virtual ~Physical();

        /**
         * Gets and sets position.
         */
        b2Vec2 getPosition() const;
        void setPosition(b2Vec2 &pos);

        /**
         * Gets and sets angle.
         */
        float getAngle() const;
        void setAngle(float angle);

        /**
         * Performs a static rotation.
         */
        void addAngle(float angle);

        /**
         * Gets and sets velocity.
         */
        b2Vec2 getLinearVelocity() const;
        void setLinearVelocity(b2Vec2 &velocity);

        /**
         * Adds the physical transform to a drawing state.
         */
        void addPhysicalTransform(sf::Transform &transform) const;
    };
}

#endif
