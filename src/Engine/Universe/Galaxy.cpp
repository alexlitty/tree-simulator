#include <tree/Engine/Universe/Galaxy.hpp>

// Constructor.
tree::Galaxy::Galaxy(std::vector<tree::Player*> &initPlayers)
: players(initPlayers)
{
    for (unsigned int i = 0; i < 10; i++) {

        // Create new planet's position.
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
    for (auto planet : this->planets) {
        delete planet;
    }

    for (auto seed : this->seeds) {
        delete seed;
    }
}

// Simulates the galaxy.
void tree::Galaxy::act()
{
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
