#include <tree/Engine/Universe/Universe.hpp>

// Constructor.
tree::Universe::Universe()
{
    Galaxy *galaxy = new Galaxy();
    this->galaxies.push_back(galaxy);
}

// Destructor.
tree::Universe::~Universe()
{
    for (auto galaxy : galaxies) {
        galaxy->disable();
        delete galaxy;
    }
}

// Emulate the universe.
bool tree::Universe::act(tree::Stage &stage)
{
    for (auto galaxy : galaxies) {
        galaxy->act(stage);
    }

    return true;
}
