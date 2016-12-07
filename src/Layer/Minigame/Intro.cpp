#include <tree/Layer/Minigame/Intro.hpp>
#include <tree/Math.hpp>

tree::Layer::IntroMinigame::IntroMinigame(sf::RenderWindow& initWindow, std::vector<tree::Player*>& initPlayers)
: window(initWindow),
  players(initPlayers),
  launchDistance(0.0f),
  maxLaunchDistance(50.0f)
{
    Angle startingAngle;
    startingAngle.radians(THREE_HALVES_PI);
    this->players[0]->setAngle(startingAngle);
    this->players[0]->setPosition(tree::VectorZero);

    this->players[0]->elements.add(Element::Hydrogen);
    this->players[0]->generate();

    // Create home planet.
    this->homePlanet = new Planet(Vector(0, 25.0f));
    this->homePlanet->elements.add(Element::Hydrogen, 10);
    this->homePlanet->generate();
}

tree::Layer::IntroMinigame::~IntroMinigame()
{
    delete homePlanet;
}

void tree::Layer::IntroMinigame::updateViews()
{
    Vector windowSize(this->window.getSize().x, this->window.getSize().y);
    float resolution = windowSize.x / windowSize.y;

    Vector gameViewSize;
    gameViewSize.y = 100.0f;
    gameViewSize.x = gameViewSize.y * resolution;
    this->gameView.setSize(gameViewSize);
    this->gameView.setCenter(this->players[0]->getPosition());
}

bool tree::Layer::IntroMinigame::execute(std::vector<sf::Event>& events)
{
    this->updateViews();
    //this->homePlanet->prepare();

    this->launchDistance = this->players[0]->getPosition().distance(this->homePlanet->getPosition());
    return this->launchDistance < this->maxLaunchDistance;
}

void tree::Layer::IntroMinigame::draw()
{
    float launchPercent = this->launchDistance / this->maxLaunchDistance;

    sf::Color skyColor = sf::Color::Black;
    skyColor.r = 125 - (launchPercent * 125);
    skyColor.b = 255 - (launchPercent * 255);
    this->window.clear(skyColor);

    this->window.setView(this->gameView);
    this->homePlanet->draw(this->window, this->renderStates);
    this->players[0]->draw(this->window, this->renderStates);
}
