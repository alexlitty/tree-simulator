#include <tree/Engine/Universe/Universe.hpp>

// Constructor.
tree::Universe::Universe()
{
    // Initialize players.
    this->players.push_back(new tree::Player());

    // Initialize galaxies.
    Galaxy *galaxy = new Galaxy(this->players);
    this->galaxies.push_back(galaxy);
}

// Destructor.
tree::Universe::~Universe()
{
    // Destroy galaxies.
    for (auto galaxy : galaxies) {
        delete galaxy;
    }

    // Destroy players.
    for (auto player : players) {
        delete player;
    }
}

// Get the center of camera focus.
tree::Vector tree::Universe::getFocusCenter() const
{
    return this->galaxies[0]->getFocusCenter();
}

// Emulate the universe.
void tree::Universe::act()
{
    for (auto galaxy : galaxies) {
        galaxy->act();
    }
}

// Draw the universe.
void tree::Universe::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw galaxies.
    for (auto galaxy : this->galaxies) {
        galaxy->draw(target, states);
    }
}
