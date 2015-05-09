#ifndef TREESIMULATOR_LAYER_GAME
#define TREESIMULATOR_LAYER_GAME

#include <chrono>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../Object/Background/Stars.hpp"
#include "../Object/Player.hpp"
#include "Type.hpp"

namespace tree
{
    namespace Layer
    {
        class Game : public Layer::Type
        {
            // Rendering window for the Game.
            sf::RenderWindow &m_window;

            // Current rendering state.
            sf::RenderStates m_render_states;

            // Current viewport.
            sf::View m_view;

            // Main player.
            Player m_player;

            // Timer, for real-time physics calculations.
            std::chrono::time_point<std::chrono::system_clock> m_timer;

            // Indication that the Game has begun execution.
            bool m_executing;

            // Collection of objects which Physically interact with each other.
            std::vector<tree::Physical*> m_physical;

            // Collection of drawable objects.
            std::vector<tree::Drawable*> m_drawable;

            // Background stars.
            std::vector<tree::Background::Stars*> m_background;

        public:
            /**
             * Constructor.
             */
            Game(sf::RenderWindow &window);

            /**
             * Deconstructor.
             */
            ~Game();

            /**
             * Return the current timed duration, and restart the timer.
             */
            float elapsedTime();

            /**
             * Execute the Game.
             */
            virtual bool execute(std::vector<sf::Event> &events) override;
        };
    }
}

#endif
