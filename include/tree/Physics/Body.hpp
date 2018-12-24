#pragma once

#include <Box2D/Box2D.h>

namespace tree
{
    namespace physics
    {
        class Body
        {
        protected:
            b2Body* body;

        public:
            Body();
            ~Body();
        };
    }
}
