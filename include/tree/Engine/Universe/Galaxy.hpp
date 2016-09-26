#ifndef TREESIMULATOR_ENGINE_UNIVERSE_GALAXY_HPP
#define TREESIMULATOR_ENGINE_UNIVERSE_GALAXY_HPP

#include <tree/Object/Background/Stars.hpp>
#include <tree/Object/Planet.hpp>
#include <tree/Object/Player.hpp>
#include <tree/Object/Weapon/Seed.hpp>

namespace tree
{
    class Galaxy
    {
        // Reference to players.
        std::vector<tree::Player*> players;

        // Backgrounds.
        std::vector<tree::Background::Stars*> backgrounds;

        // Planets in this galaxy.
        std::vector<Planet*> planets;

        // @@@ seeds
        std::vector<tree::weapon::Seed*> seeds;

    public:

        /**
         * Constructor.
         */
        Galaxy(std::vector<tree::Player*> &initPlayers);

        /**
         * Destructor.
         *
         * Assumes the galaxy is already disabled.
         */
        virtual ~Galaxy();

        /**
         * Get the center of camera focus.
         */
        tree::Vector getFocusCenter() const;

        /**
         * Emulates the galaxy.
         */
        void act();

        /**
         * Draws the galaxy.
         */
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}

#endif
