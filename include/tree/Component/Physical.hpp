#ifndef TREESIMULATOR_COMPONENT_PHYSICAL_HPP
#define TREESIMULATOR_COMPONENT_PHYSICAL_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <tree/Component/Drawable.hpp>
#include <tree/Math.hpp>
#include <tree/Physics/Body.hpp>
#include <tree/Physics/World.hpp>

namespace tree
{
    /**
     * A physical object in the game world.
     *
     * Physics powered by Box2D.
     */
    class Physical : virtual public Drawable
    {
    protected:
        physics::Body body;

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

        // Current thrust power.
        float m_currentThrustPower = 0.0f;

        // Default torque power.
        float m_torquePower = 75000.0f;

        // Default rotation power.
        float m_rotationPower = 0.1f;

        // Total force being applied on the next step.
        b2Vec2 m_totalForce;

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
         * Enables and disables physics.
         */
        void enablePhysics();
        void disablePhysics();

        /**
         * Add a fixture.
         */
        b2Fixture* addFixture(b2FixtureDef &fixtureDef);

        /**
         * Updates the mass of this body.
         */
        void updateMass();

        /**
         * Add a distance joint.
         */
        void distanceJoint(Physical &other, Vector thisPosition, Vector otherPosition, bool localize = true);

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
        virtual void onCollision(Physical *other);

        /**
         * Gets mass.
         */
        float getMass() const;

        /**
         * Gets and sets position.
         */
        Vector getPosition() const;
        sf::Vector2f getPixelPosition() const;
        void setPosition(Vector position);

        /**
         * Gets position, plus an angled distance.
         */
        Vector getAngledPosition(float magnitude, Angle angle) const;

        /**
         * Gets and sets angle.
         */
        Angle getAngle() const;
        void setAngle(Angle angle);

        /**
         * Performs a rotation.
         */
        void rotate(bool direction);
        void rotate(Angle angle);

        /**
         * Gets and sets fixed rotation.
         */
        bool getFixedRotation() const;
        void setFixedRotation(bool fixed);

        /**
         * Gets and sets velocity.
         */
        Vector getLinearVelocity() const;
        void setLinearVelocity(Vector velocity);

        /**
         * Applies force to this object.
         */
        void applyForce(const Vector force);

        /**
         * Applies thrust to this object.
         *
         * Uses internal thrust power.
         */
        void applyThrust(bool direction);

        /**
         * Whether this object is currently thrusting.
         */
        bool isThrusting() const;

        /**
         * Gets current thrusting power.
         */
        float getCurrentThrust() const;

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
         * Gets the total force being applied next step.
         */
        Vector getTotalForce() const;

        /**
         * Prepares this object for another physics step.
         */
        void prepare();

        /**
         * Estimates the next linear velocity.
         */
        Vector estimateLinearVelocity() const;

        /**
         * Gets the current physical transform.
         */
        sf::Transform getPhysicalTransform() const;

        /**
         * Transforms a local vector to a global vector.
         */
        Vector applyTransform(Vector vector) const;

        /**
         * Adds the physical transform to a drawing state.
         */
        void addPhysicalTransform(sf::Transform &transform) const;
    };
}

#endif
