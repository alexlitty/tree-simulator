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

        /**
         * List of active joints.
         */
        std::vector<b2Joint*> m_joints;

    public:

        // Whether this object creates gravitational forces.
        bool createsGravity = false;

        // Whether this object feels gravitational forces.
        bool feelsGravity = true;

        /**
         * Constructor.
         */
        Physical();

        /**
         * Destructor.
         */
        virtual ~Physical();

        /**
         * Add a fixture.
         */
        void addFixture(b2FixtureDef &fixtureDef);

        /**
         * Add a distance joint.
         */
        void distanceJoint(Physical &other, b2Vec2 thisPosition, b2Vec2 otherPosition, bool localize = true);

        /**
         * Adds a joint to be tracked.
         */
        void trackJoint(b2Joint *joint);

        /**
         * Removes a joint.
         */
        void removeJoint(b2Joint *joint, bool fromOther = false);

        /**
         * Handle a collision with another physical object.
         */
        virtual void onCollision(Physical &other);

        /**
         * Gets mass.
         */
        float getMass() const;

        /**
         * Gets and sets position.
         */
        b2Vec2 getPosition() const;
        sf::Vector2f getPixelPosition() const;
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
         * Sets fixed rotation.
         */
        void setFixedRotation(bool fixed);

        /**
         * Gets and sets velocity.
         */
        b2Vec2 getLinearVelocity() const;
        void setLinearVelocity(b2Vec2 &velocity);

        /**
         * Applies force to this object.
         */
        void applyForce(const b2Vec2 &force);

        /**
         * Applies gravity from a gravity source.
         */
        void applyGravity(Physical &other);

        /**
         * Adds the physical transform to a drawing state.
         */
        void addPhysicalTransform(sf::Transform &transform) const;
    };
}

#endif
