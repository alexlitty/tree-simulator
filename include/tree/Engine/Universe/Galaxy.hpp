#ifndef TREESIMULATOR_ENGINE_UNIVERSE_GALAXY_HPP
#define TREESIMULATOR_ENGINE_UNIVERSE_GALAXY_HPP

#include <tree/Component/Actor.hpp>
#include <tree/Object/Planet.hpp>

namespace tree
{
    class Galaxy : public Actor
    {
        // Global origin of this galaxy.
        Vector origin;

        // Planets in this galaxy.
        std::vector<Planet*> planets;

        // Whether this galaxi is enabled.
        bool enabled;

    public:

        Galaxy();
        ~Galaxy();

        /**
         * Enables and disables galaxy activity.
         */
        virtual void enable(Stage &stage);
        virtual void disable();

        /**
         * Emulates the galaxy.
         */
        bool act(Stage &stage);
    };
}

#endif
