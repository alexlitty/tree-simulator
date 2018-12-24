#pragma once

#include <tree/Math/Vector.hpp>

namespace tree
{
    namespace physics
    {
        class Body
        {
        protected:
            b2Body* body;

        public:
            Body(
                bool dynamic = true,
                tree::Vector position = tree::VectorZero
            );

            ~Body();

            void updateMass();

            /**
             * Owner.
             */
            void setOwner(void *owner);
            void* getOwner();

            /**
             * Position.
             */
            void setPosition(tree::Vector position);
            tree::Vector getPosition() const;
            tree::Vector getPixelPosition() const;

            /**
             * Angle.
             */
            void setAngle(tree::Angle angle);
            tree::Angle getAngle() const;

            /**
             * Fixed rotation.
             */
            void setFixedRotation(bool fixedRotation);
            bool getFixedRotation() const;

            /**
             * Linear velocity.
             */
            void setLinearVelocity(tree::Vector velocity);
            tree::Vector getLinearVelocity() const;

            /**
             * Applying force.
             */
            void applyForce(tree::Vector force);
            void applyTorque(float torque);

            /**
             * Miscellaneous setters.
             */
            void setType(b2BodyType type);
            void setAngularDamping(float angularDamping);

            /**
             * Miscellaneous getters.
             */
            float getMass() const;
            b2Body* getInternalBody();
        };
    }
}
