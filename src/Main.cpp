#include <iostream>
#include <vector>
#include <tree/Layer/Root.hpp>
#include <tree/Physics/Collisions.hpp>

int main()
{
    // Disable SFML output.
    //sf::err().rdbuf(nullptr);

    // Prepare Box2D.
    tree::world.SetContactListener(&tree::collisions);

    // Prepare events container.
    std::vector<sf::Event> events;

    try {
        tree::Layer::Root treesimulator;
        while (treesimulator.execute(events)) { }
        return 0;
    }

    catch (const std::exception& ex) {
        std::cout << "Timber! Tree Simulator has stopped: " << ex.what() << std::endl;
    }
    return 1;
}
