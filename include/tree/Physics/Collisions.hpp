#ifndef TREESIMULATOR_PHYSICS_COLLISIONS_HPP
#define TREESIMULATOR_PHYSICS_COLLISIONS_HPP

#include <list>
#include <Box2D/Box2D.h>
#include <tree/Component.hpp>

namespace tree
{
    class ContactListener : public b2ContactListener
    {
        // Internal list of collisions.
        std::list<std::pair<Physical*, Physical*>> m_collisions;

    public:

        /**
         * Listen for collisions.
         */
        void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);

        /**
         * Clear collisions.
         */
        void clear();

        /**
         * Resolve the non-physical effects of collisions.
         */
        void resolve();
    };

    // Global instance of contact listener.
    extern ContactListener collisions;
}

#endif
