#ifndef TREESIMULATOR_COMPONENT_PHYSICAL_HPP
#define TREESIMULATOR_COMPONENT_PHYSICAL_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <tree/Component/Object.hpp>
#include <tree/Physics/World.hpp>

namespace tree
{
    /**
     * A physical object in the game world.
     *
     * Physics powered by Box2D.
     */
    class Physical : virtual public Object
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

        // List of active joints.
        std::vector<b2Joint*> m_joints;

        // Default thrust power.
        float m_thrustPower = 7500.0f;

        // Default torque power.
        float m_torquePower = 75000.0f;

        // Default rotation power.
        float m_rotationPower = 0.1f;

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
        b2Fixture* addFixture(b2FixtureDef &fixtureDef);

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
         * Gets position, plus an angled distance.
         */
        b2Vec2 getAngledPosition(float magnitude, float angle = 0) const;

        /**
         * Gets and sets angle.
         */
        float getAngle() const;
        void setAngle(float angle);

        /**
         * Performs a rotation.
         */
        void rotate(bool direction);
        void rotate(float angle);

        /**
         * Gets and sets fixed rotation.
         */
        bool getFixedRotation() const;
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
         * Applies thrust to this object.
         *
         * Uses internal thrust power.
         */
        void applyThrust(bool direction);

        /**
         * Applies torque to this object.
         *
         * Uses internal torque power.
         */
        void applyTorque(bool direction);

        /**
         * Applies gravity from a gravity source.
         */
        void applyGravity(Physical &other);
        void applyGravity(Physical *other);

        /**
         * Adds the physical transform to a drawing state.
         */
        void addPhysicalTransform(sf::Transform &transform) const;
    };
}

#endif
