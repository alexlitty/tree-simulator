#ifndef TREESIMULATOR_ENGINE_UNIVERSE_GALAXY_HPP
#define TREESIMULATOR_ENGINE_UNIVERSE_GALAXY_HPP

#include <tree/Object/Background/Stars.hpp>
#include <tree/Object/Boundary/Circle.hpp>
#include <tree/Object/Planet.hpp>
#include <tree/Object/Player.hpp>
#include <tree/Object/Weapon/Seed.hpp>
#include <tree/Object/WormholeEntrance.hpp>

namespace tree
{
    class Galaxy
    {
        // Reference to players.
        std::vector<tree::Player*> players;

        // Backgrounds.
        std::vector<tree::Background::Stars*> backgrounds;

        // Boundary.
        boundary::Circle boundary;

        // Planets in this galaxy.
        std::vector<Planet*> planets;

        // Wormhole entrances in this galaxy.
        std::vector<WormholeEntrance*> wormholeEntrances;

        // @@@ seeds
        std::vector<tree::weapon::Seed*> seeds;

        // Whether this galaxy is locked for animations.
        bool isLocked = false;

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
         * Locks and unlocks the galaxy for animations.
         */
        void lock();
        void unlock();

        /**
         * Emulates the galaxy.
         */
        bool act();

        /**
         * Draws the galaxy.
         */
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}

#endif
