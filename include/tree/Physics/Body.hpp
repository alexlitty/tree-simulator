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

            void setOwner(void *owner);
            void setType(b2BodyType type);
            void setAngularDamping(float angularDamping);
            void setFixedRotation(bool fixedRotation);

            b2Body* getInternalBody();
        };
    }
}
