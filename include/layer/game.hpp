#ifndef TREESIMULATOR_LAYER_GAME
#define TREESIMULATOR_LAYER_GAME

#include <chrono>
#include <vector>

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

            // Current rendering state.
            sf::RenderStates render_states;

            // Main player.
            player m_player;

            // Timer, for real-time physics calculations.
            std::chrono::time_point<std::chrono::system_clock> m_timer;

            // Indication that the game has begun execution.
            bool m_executing;

            // Collection of objects which physically interact with each other.
            std::vector<tree::physical*> m_physical;

            // Collection of drawable objects.
            std::vector<tree::drawable*> m_drawable;

        public:
            /**
             * Constructor.
             */
            game(sf::RenderWindow &window);

            /**
             * Deconstructor.
             */
            ~game();

            /**
             * Return the current timed duration, and restart the timer.
             */
            float elapsed_time();

            /**
             * Execute the game.
             */
            virtual bool execute(std::vector<sf::Event> &events) override;
        };
    }
}

#endif
