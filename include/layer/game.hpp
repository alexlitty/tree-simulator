#ifndef TREESIMULATOR_LAYER_GAME
#define TREESIMULATOR_LAYER_GAME

#include <SFML/Graphics.hpp>
#include "../object/player.hpp"
#include "../layer.hpp"

namespace tree
{
    namespace layer
    {
        class game : public layer_t
        {
            // Rendering window for the game.
            sf::RenderWindow &m_window;

            // Main player.
            player m_player;

        public:
            /**
             * Constructor.
             */
            game(sf::RenderWindow &window);

            /**
             * Execute the game.
             */
            virtual bool execute(std::vector<sf::Event> &events) override;
        };
    }
}

#endif
