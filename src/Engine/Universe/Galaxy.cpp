#include <limits>
#include <tree/Engine/Universe/Galaxy.hpp>
#include <tree/Utility/Collection.hpp>

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

        ElementCollection elements;
        switch (tree::random(0, 5)) {
            case 0:
                elements.add(Element::Oxygen, tree::random(10, 20));
                break;

            case 1:
            case 2:
                elements.add(Element::Hydrogen, tree::random(10, 20));
                break;

            default:
                int result = tree::random(10, 20);
                elements.add(Element::Hydrogen, result * 2);
                elements.add(Element::Oxygen, result);
                break;
        }

        MoleculeCollection molecules;
        while (!elements.isEmpty()) {
            Molecule molecule(elements);
            molecules.add(molecule);
        }

        planet->receiveMolecules(molecules);
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

    // Handle planet absorptions.
    for (auto player : this->players) {

        // Try to absorb a planet.
        if (planets.size() && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

            // Find something to absorb.
            if (!player->isAbsorbing()) {

                // Find nearest planet.
                int currentDistance;
                int smallestDistance = std::numeric_limits<int>::max();
                tree::Planet *closestPlanet = nullptr;
                for (auto planet : this->planets) {
                    currentDistance = planet->getPosition().distance(
                        this->players[0]->getPosition()
                    );

                    if (smallestDistance > currentDistance) {
                        smallestDistance = currentDistance;
                        closestPlanet = planet;
                    }
                }

                // Start absorbing from planet.
                player->setAbsorptionTarget(closestPlanet);
            }

            // Absorb.
            tree::Planet *absorptionTarget = player->getAbsorptionTarget();
            if (absorptionTarget->canCrumble()) {
                player->absorb();
            }

            // Planet totally absorbed. Destroy it.
            else {
                player->takeAbsorptionTarget();

                tree::remove(this->planets, absorptionTarget);
                delete absorptionTarget;
            }
        }

        // Stop absorbing.
        else {
            tree::Planet *absorptionTarget = player->getAbsorptionTarget();

            if (absorptionTarget) {
                absorptionTarget->restoreHealth();
                player->resetAbsorptionTarget();
            }
        }
    }

    // Planet acting.
    for (auto planet : this->planets) {
        planet->act();
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
