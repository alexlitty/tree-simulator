#include <layer/game.hpp>

// Constructor.
tree::layer::game::game(sf::RenderWindow &window)
: m_window(window)
{

}

// Execute the game.
bool tree::layer::game::execute(std::vector<sf::Event> &events)
{
    return true;
}
