#ifndef TREESIMULATOR_LAYER_MINIGAME_INTRO_HPP
#define TREESIMULATOR_LAYER_MINIGAME_INTRO_HPP

#include <tree/Layer/Type.hpp>
#include <tree/Object/Player.hpp>

namespace tree
{
    namespace Layer
    {
        class IntroMinigame : public Layer::Type
        {
            sf::RenderWindow& window;
            sf::RenderStates renderStates;
            sf::View interfaceView;

            std::vector<Player*>& players;

            float launchDistance;
            float maxLaunchDistance;

        public:
            sf::View gameView;

            Planet *homePlanet;

            IntroMinigame(sf::RenderWindow& initWindow, std::vector<Player*>& initPlayers);
            ~IntroMinigame();

            void updateViews();
            virtual bool execute(std::vector<sf::Event>& events) override;
            void draw();
        };
    }
}

#endif
