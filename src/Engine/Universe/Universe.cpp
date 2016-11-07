#include <tree/Engine/Universe/Universe.hpp>

// Constructor.
tree::Universe::Universe(std::vector<tree::Player*> &_players)
: players(_players),
  currentGalaxy(nullptr)
{
    this->setNextGalaxy();
}

// Destructor.
tree::Universe::~Universe()
{
    this->destroyWormhole();
    this->destroyGalaxy();
}

// Get the center of camera focus.
tree::Vector tree::Universe::getFocusCenter() const
{
    if (this->currentGalaxy) {
        return this->currentGalaxy->getFocusCenter();
    }

    return tree::VectorZero;
}

// Sets the next galaxy to play in.
void tree::Universe::setNextGalaxy()
{
    this->destroyGalaxy();
    this->currentGalaxy = new Galaxy(this->players);

    // Reset player positions.
    for (auto player : this->players) {
        player->setPosition(tree::VectorZero);
        player->setLinearVelocity(tree::VectorZero);
    }
}

// Destroys the current galaxy.
void tree::Universe::destroyGalaxy()
{
    if (this->currentGalaxy) {
        delete this->currentGalaxy;
    }

    this->currentGalaxy = nullptr;
}

// Destroys the current wormhole.
void tree::Universe::destroyWormhole()
{
    if (this->wormhole) {
        delete this->wormhole;
        this->wormhole = nullptr;
    }
}

// Emulate the universe.
void tree::Universe::act()
{
    if (this->currentGalaxy) {
        if (this->currentGalaxy->act()) {
            this->setNextGalaxy();
        }
    }
}

// Draw the universe.
void tree::Universe::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Draw galaxy.
    if (this->currentGalaxy) {
        this->currentGalaxy->draw(target, states);
    }

    // Draw players.
    for (auto player : players) {
        player->draw(target, states);
    }
}
