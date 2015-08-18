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

            // Players.
            Player *m_player;

            // Collection of drawable objects.
            std::vector<tree::Drawable*> m_drawable;

            // Collection of physical objects.
            std::vector<tree::Physical*> m_physical;

            // Collection of acting objects.
            std::vector<tree::Actor*> m_actor;

            // Collection of expirable objects.
            std::vector<tree::Expirable*> m_expirable;

            // Temporary collections of objects.
            tree::Objects m_objects;
            std::set<tree::Object*> m_objectsDestroy;

            // Background stars.
            std::vector<tree::Background::Stars*> m_background;

            // FPS information.
            sf::Text m_framesText;
            unsigned int m_frames;
            sf::Clock m_framesClock;

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
             * Execute the Game.
             */
            virtual bool execute(std::vector<sf::Event> &events) override;
        };
    }
}

#endif
