#include <tree/Engine/Universe/Galaxy.hpp>

/**
 * Constructor.
 */
tree::Galaxy::Galaxy()
: enabled(false)
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
                planet->nuggets.add(tree::nugget::lava, amount / 4);
                planet->nuggets.add(tree::nugget::plasma, amount);
                planet->nuggets.add(tree::nugget::rock, 1);
        }

        // Generate planet.
        planet->generate();
        planets.push_back(planet);
    }
}

/**
 * Destructor.
 */
tree::Galaxy::~Galaxy()
{

}

/**
 * Enables the galaxy.
 */
void tree::Galaxy::enable(tree::Stage &stage)
{
    this->enabled = true;
    this->stage = &stage;

    for (auto planet : planets) {
        planet->enablePhysics();
        this->stage->add(planet);
    }
}

/**
 * Disables the galaxy.
 */
void tree::Galaxy::disable()
{
    enabled = false;

    for (auto planet : planets) {
        planet->disablePhysics();
        this->stage->remove(planet);
    }
}

/**
 * Emulates the galaxy.
 */
bool tree::Galaxy::act(tree::Stage &stage)
{
    if (!enabled) {
        this->enable(stage);
    }

    return true;
}
