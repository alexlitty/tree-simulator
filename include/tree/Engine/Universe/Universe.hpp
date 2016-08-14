#ifndef TREESIMULATOR_ENGINE_UNIVERSE_UNIVERSE_HPP
#define TREESIMULATOR_ENGINE_UNIVERSE_UNIVERSE_HPP

#include <tree/Engine/Universe/Galaxy.hpp>
#include <tree/Object/Player.hpp>

namespace tree
{
    class Universe : public Drawable
    {
        // Players.
        std::vector<tree::Player*> players;

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
         * Get the center of camera focus.
         */
        tree::Vector getFocusCenter() const;

        /**
         * Emulate the universe.
         */
        void act();

        /**
         * Draw the universe.
         */
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}

#endif
