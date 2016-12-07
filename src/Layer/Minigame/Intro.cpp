#include <tree/Layer/Minigame/Intro.hpp>
#include <tree/Math.hpp>

tree::Layer::IntroMinigame::IntroMinigame(sf::RenderWindow& initWindow, std::vector<tree::Player*>& initPlayers)
: window(initWindow),
  players(initPlayers),
  ground(100.0f, 120)
{
    this->ground.setFillColor(sf::Color::Green);
    tree::centerOrigin(this->ground);
    this->ground.setPosition(100.0f, 50.0f);

    Angle startingAngle;
    startingAngle.radians(THREE_HALVES_PI);
    this->players[0]->setAngle(startingAngle);
    this->players[0]->setPosition(tree::VectorZero);
}

void tree::Layer::IntroMinigame::updateViews()
{
    Vector windowSize(this->window.getSize().x, this->window.getSize().y);
    float resolution = windowSize.x / windowSize.y;

    Vector gameViewSize;
    gameViewSize.y = 50.0f;
    gameViewSize.x = gameViewSize.y * resolution;
    this->gameView.setSize(gameViewSize);
    this->gameView.setCenter(this->players[0]->getPosition());
}

bool tree::Layer::IntroMinigame::execute(std::vector<sf::Event>& events)
{
    this->updateViews();
    return true;
}

void tree::Layer::IntroMinigame::draw()
{
    this->window.clear(sf::Color::Blue);

    this->window.setView(this->gameView);
    this->players[0]->draw(this->window, this->renderStates);
}
