#ifndef TREESIMULATOR_COMPONENT_INTEL_HPP
#define TREESIMULATOR_COMPONENT_INTEL_HPP

#include <tree/Component/Actor.hpp>
#include <tree/Component/Physical.hpp>

namespace tree
{
    /**
     * A being of intelligence.
     */
    class Intel : virtual public Actor, virtual public Physical
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
        void faceTarget(b2Vec2 &target);

        /**
         * Blindly move toward a target position.
         */
        void moveBlindly(b2Vec2 &target);

        /**
         * Maintains a distance from a target position.
         */
        void maintainDistance(b2Vec2 target, float distance);
    };
}

#endif
