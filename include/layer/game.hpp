#ifndef TREESIMULATOR_LAYER_GAME
#define TREESIMULATOR_LAYER_GAME

#include <SFML/Graphics.hpp>
#include "../layer.hpp"

namespace tree
{
    namespace layer
    {
        class game : public layer_t
        {
            sf::RenderWindow &m_window;

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
