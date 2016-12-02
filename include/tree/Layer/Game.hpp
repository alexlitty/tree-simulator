#ifndef TREESIMULATOR_LAYER_GAME
#define TREESIMULATOR_LAYER_GAME

#include <chrono>
#include <set>
#include <vector>
#include <SFML/Graphics.hpp>

#include <tree/Component.hpp>
#include <tree/Engine/Universe/Universe.hpp>
#include <tree/Gui/Radar.hpp>
#include <tree/Layer/Type.hpp>
#include <tree/Object/Background/Stars.hpp>
#include <tree/Object/Player.hpp>

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
            sf::View m_viewGame;
            sf::View m_viewInterface;

            // Game universe.
            tree::Universe *universe;

            // Collection of players.
            std::vector<tree::Player*> players;

            // Gui objects.
            tree::Radar radar;

            // Debug mode objects.
            sf::Text debugText;
            unsigned int debugFrames;
            sf::Clock debugFramesClock;

        public:
            /**
             * Constructor.
             */
            Game(sf::RenderWindow &window);

            /**
             * Destructor.
             */
            ~Game();

            /**
             * Updates views.
             *
             * If immediate is false, view is updated slowly.
             */
            void updateViews(bool immediate = false);

            /**
             * Execute the Game.
             */
            bool execute(std::vector<sf::Event> &events) override;
        };
    }
}

#endif
