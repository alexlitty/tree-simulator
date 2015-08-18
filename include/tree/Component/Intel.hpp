#ifndef TREESIMULATOR_COMPONENT_INTEL_HPP
#define TREESIMULATOR_COMPONENT_INTEL_HPP

#include <Box2D/Box2D.h>
#include <tree/Component/Object.hpp>

namespace tree
{
    class Intel : virtual public Object
    {

        b2Vec2 m_intelTarget;

    public:
        /**
         * Constructor.
         */
        Intel();

        /**
         * Set the current target.
         */
        //void setIntelTarget(b2Vec2 &target);
    };
}

#endif
