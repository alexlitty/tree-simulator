#include <layer/game.hpp>

// Constructor.
tree::layer::game::game(sf::RenderWindow &window)
: m_window(window)
{

}

// Execute a game tick.
bool tree::layer::game::execute(std::vector<sf::Event> &events)
{
    float delta = 1;

    // Left key pressed.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_player.accelerate_horizontal(-delta);
    }

    // Right key pressed.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_player.accelerate_horizontal(delta);
    }

    m_player.pass_time(0.1f);

    // Draw player.
    m_window.draw(m_player);

    // End this tick.
    return true;
}
