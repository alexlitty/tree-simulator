#ifndef TREESIMULATOR_OBJECT_PARTICLES_NUGGET_CRUMBS
#define TREESIMULATOR_OBJECT_PARTICLES_NUGGET_CRUMBS

#include <tree/Object/Particles.hpp>

namespace tree
{
    class NuggetCrumbs : public Particles
    {
    public:
        /**
         * Constructor.
         */
        NuggetCrumbs();

        /**
         * Animates the crumbs.
         */
        void animate(tree::Vector target);
    };
}

#endif
