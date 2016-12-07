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

            std::vector<Player*>& players;
            sf::CircleShape ground;

            sf::View gameView;
            sf::View interfaceView;

        public:
            IntroMinigame(sf::RenderWindow& initWindow, std::vector<Player*>& initPlayers);

            void updateViews();

            virtual bool execute(std::vector<sf::Event>& events) override;

            void draw();
        };
    }
}

#endif
