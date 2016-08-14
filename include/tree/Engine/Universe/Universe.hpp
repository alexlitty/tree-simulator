#ifndef TREESIMULATOR_ENGINE_UNIVERSE_UNIVERSE_HPP
#define TREESIMULATOR_ENGINE_UNIVERSE_UNIVERSE_HPP

#include <tree/Component/Actor.hpp>
#include <tree/Engine/Universe/Galaxy.hpp>
#include <tree/Object/Player.hpp>
#include <tree/Utility/Stage.hpp>

namespace tree
{
    class Universe : public Actor
    {
        // All galaxies in the universe.
        std::vector<Galaxy*> galaxies;



    public:

        /**
         * Constructor.
         */
        Universe();

        /**
         * Deconstructor.
         */
        ~Universe();

        /**
         * Emulate the universe.
         */
        virtual bool act(Stage &stage) override;
    };
}

#endif
