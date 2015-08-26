#ifndef TREESIMULATOR_LAYER_GAME
#define TREESIMULATOR_LAYER_GAME

#include <chrono>
#include <set>
#include <vector>
#include <SFML/Graphics.hpp>

#include <tree/Component.hpp>
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

            // Stage of objects.
            tree::Stage m_stage;

            // Quick pointer to player.
            Player *m_player;

            // Background stars.
            std::vector<tree::Background::Stars*> m_background;

            // FPS information.
            sf::Text m_framesText;
            unsigned int m_frames;
            sf::Clock m_framesClock;

            // Player information.
            sf::Text m_positionText;
            sf::Text m_velocityText;

            // Editor information.
            tree::Layer::PlayerEditor *m_playerEditor;
            float m_editingAlpha = 1.0f;

        public:
            /**
             * Constructor.
             */
            Game(sf::RenderWindow &window);

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
