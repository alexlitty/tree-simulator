#include <iostream>
#include <vector>
#include <layer/root.hpp>

int main()
{
    // Disable SFML output.
    sf::err().rdbuf(nullptr);

    // Prepare events container.
    std::vector<sf::Event> events;

    try {
        tree::layer::root treesimulator;
        while (treesimulator.execute(events)) { }
        return 0;
    }

    catch (const std::exception& ex) {
        std::cout << "Timber! Tree Simulator has stopped: " << ex.what() << std::endl;
    }
    return 1;
}
