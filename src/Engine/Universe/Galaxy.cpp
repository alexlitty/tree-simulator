#include <tree/Engine/Universe/Galaxy.hpp>

// Constructor.
tree::Galaxy::Galaxy(std::vector<tree::Player*> &initPlayers)
: players(initPlayers)
{
    // Initialize backgrounds.
    for (unsigned int i = 0; i < 10; i++) {
        tree::Background::Stars *bg = new tree::Background::Stars(
            10000,
            std::pow((i + 2)*1.0f, 2)
        );

        this->backgrounds.push_back(bg);
    }

    // Create planets.
    for (unsigned int i = 0; i < 10; i++) {
        Vector planetPosition(
            tree::random(-100.0f, 100.0f),
            tree::random(-100.0f, 100.0f)
        );

        // Create planet.
        Planet *planet = new Planet(planetPosition);
        planet->applyTorque(true);

        // Set nugget makeup.
        unsigned int amount = tree::random(1, 20);
        switch (tree::random(1, 4)) {
            case 1:
                planet->nuggets.add(tree::nugget::lava, amount);
                break;

            case 2:
                planet->nuggets.add(tree::nugget::rock, amount);
                break;

            case 3:
                planet->nuggets.add(tree::nugget::plasma, amount);
                break;

            default:
                planet->nuggets.add(tree::nugget::lava, 2);
                planet->nuggets.add(tree::nugget::plasma, amount);
                planet->nuggets.add(tree::nugget::rock, 1);
        }

        // Generate planet.
        planet->generate();
        planet->enablePhysics();
        this->planets.push_back(planet);
    }
}

// Destructor.
tree::Galaxy::~Galaxy()
{
    for (auto background : this->backgrounds) {
        delete background;
    }

    for (auto planet : this->planets) {
        delete planet;
    }

    for (auto seed : this->seeds) {
        delete seed;
    }
}

// Get the center of camera focus.
tree::Vector tree::Galaxy::getFocusCenter() const
{
    return this->players[0]->getPixelPosition();
}

// Simulates the galaxy.
void tree::Galaxy::act()
{
    // Adjust backgrounds.
    for (auto background : this->backgrounds) {
        background->setViewTarget(this->getFocusCenter());
    }

    // Prepare physicals.
    for (auto planet : this->planets) {
        planet->prepare();
    }
    for (auto seed : this->seeds) {
        seed->prepare();
    }
    for (auto player : this->players) {
        player->prepare();
    }

    // Player acting.
    for (auto player : this->players) {
        player->act(this->seeds);
    }
}

// Draws the galaxy.
void tree::Galaxy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw backgrounds.
    for (auto background : this->backgrounds) {
        background->draw(target, states);
    }

    // Draw planets.
    for (auto planet : this->planets) {
        planet->draw(target, states);
    }

    // Draw weapons.
    for (auto seed : this->seeds) {
        seed->draw(target, states);
    }

    // Draw players.
    for (auto player : this->players) {
        player->draw(target, states);
    }
}
