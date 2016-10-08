#ifndef TREESIMULATOR_OBJECT_PARTICLES_PLANET_CRUMBS
#define TREESIMULATOR_OBJECT_PARTICLES_PLANET_CRUMBS

#include <tree/Object/Particles.hpp>

namespace tree
{
    class PlanetCrumbs : public Particles
    {
    public:
        /**
         * Constructor.
         */
        PlanetCrumbs();

        /**
         * Animates the crumbs.
         */
        void animate(tree::Vector target);
    };
}

#endif
