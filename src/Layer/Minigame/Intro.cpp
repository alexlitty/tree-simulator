#include <tree/Layer/Minigame/Intro.hpp>
#include <tree/Math.hpp>

tree::Layer::IntroMinigame::IntroMinigame(sf::RenderWindow& initWindow, std::vector<tree::Player*>& initPlayers)
: window(initWindow),
  players(initPlayers),
  launchDistance(0.0f)
{
    // Create home planet.
    this->homePlanet = new Planet(tree::VectorZero);
    this->homePlanet->elements.add(Element::Hydrogen, 20);
    this->homePlanet->generate();
    this->maxLaunchDistance = this->homePlanet->getRadius() * 2;

    // Set player on planet.
    Angle startingAngle;
    startingAngle.radians(THREE_HALVES_PI);
    this->players[0]->forceAngle(startingAngle);

    Vector startingPosition;
    startingPosition.x = 0.0f;
    startingPosition.y = -this->homePlanet->getRadius();
    this->players[0]->setPosition(startingPosition);
    this->players[0]->generate();
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
    this->homePlanet->prepare();
    for (auto player : this->players) {
        player->act();
        player->prepare();
    }

    this->launchDistance = this->players[0]->getPosition().distance(this->homePlanet->getPosition());
    if (!(this->launchDistance < this->maxLaunchDistance)) {
        std::cout << this->launchDistance << std::endl;
        std::cout << this->players[0]->getPosition().x << ", " << this->players[0]->getPosition().y << std::endl;
        std::cout << this->homePlanet->getPosition().x << ", " << this->homePlanet->getPosition().y << std::endl;
    }
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
    this->players[0]->draw(this->window, this->renderStates);

    // Let the player "sink" beneath the planet slightly.
    sf::RenderStates planetRenderStates = this->renderStates;
    planetRenderStates.transform.scale(1.1f, 1.1f);
    this->homePlanet->draw(this->window, planetRenderStates);
}
