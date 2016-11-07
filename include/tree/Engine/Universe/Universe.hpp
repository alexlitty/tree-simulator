#ifndef TREESIMULATOR_ENGINE_UNIVERSE_UNIVERSE_HPP
#define TREESIMULATOR_ENGINE_UNIVERSE_UNIVERSE_HPP

#include <tree/Engine/Universe/Galaxy.hpp>
#include <tree/Object/Player.hpp>
#include <tree/Universe/Wormhole.hpp>

namespace tree
{
    class Universe : public Drawable
    {
        // Players.
        std::vector<tree::Player*> players;

        // Current galaxy being played.
        Galaxy* currentGalaxy;

        // Current wormhole.
        Wormhole* wormhole = nullptr;

    public:

        /**
         * Constructor.
         */
        Universe(std::vector<tree::Player*> &_players);

        /**
         * Deconstructor.
         */
        ~Universe();

        /**
         * Get the center of camera focus.
         */
        tree::Vector getFocusCenter() const;

        /**
         * Sets the next galaxy to play in.
         */
        void setNextGalaxy();

        /**
         * Destroys the current galaxy.
         */
        void destroyGalaxy();

        /**
         * Destroys the current wormhole.
         */
        void destroyWormhole();

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
