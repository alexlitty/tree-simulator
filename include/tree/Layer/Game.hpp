#ifndef TREESIMULATOR_LAYER_GAME
#define TREESIMULATOR_LAYER_GAME

#include <chrono>
#include <set>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../Object/Background/Stars.hpp"
#include "../Object/Player.hpp"
#include "Type.hpp"

namespace tree
{
    namespace Layer
    {
        class Game : public Layer::Type, public b2ContactListener
        {
            // Rendering window for the Game.
            sf::RenderWindow &m_window;

            // Current rendering state.
            sf::RenderStates m_render_states;

            // Current viewport.
            sf::View m_view;

            // Players.
            Player *m_player;

            // Timer, for real-time physics calculations.
            std::chrono::time_point<std::chrono::system_clock> m_timer;

            // Indication that the Game has begun execution.
            bool m_executing;

            // Collection of drawable objects.
            std::vector<tree::Drawable*> m_drawable;

            // Collection of physical objects.
            std::vector<tree::Physical*> m_physical;

            // Collection of acting objects.
            std::vector<tree::Actor*> m_actor;

            // Temporary collections of objects.
            tree::Objects m_objects;
            std::set<tree::Object*> m_objectsDestroy;

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
            virtual ~Game();

            /**
             * Add temporary objects to permanent collections.
             */
            void updateObjects();

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
