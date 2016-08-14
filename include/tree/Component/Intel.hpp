#ifndef TREESIMULATOR_COMPONENT_INTEL_HPP
#define TREESIMULATOR_COMPONENT_INTEL_HPP

#include <tree/Component/Physical.hpp>

namespace tree
{
    /**
     * A being of intelligence.
     */
    class Intel : virtual public Physical
    {

        b2Vec2 m_intelTarget;

    public:
        /**
         * Constructor.
         */
        Intel();

        /**
         * Attempt to face a target.
         */
        void faceTarget(Vector& target);

        /**
         * Blindly move toward a target position.
         */
        void moveBlindly(Vector& target);

        /**
         * Maintains a distance from a target position.
         */
        void maintainDistance(Vector target, float distance);
    };
}

#endif
