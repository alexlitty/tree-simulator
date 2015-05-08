#include <cmath>
#include <set>
#include <layer/game.hpp>
#include <object/planet.hpp>

// Constructor.
tree::layer::game::game(sf::RenderWindow &window)
: m_window(window),
  m_executing(false)
{
    sf::Vector2f position(100, 100);
    m_player.set_position(position);
    m_physical.push_back(&m_player);
    m_drawable.push_back(&m_player);

    // Create a gravity source.
    position.x = position.y = 300;
    tree::planet* object = new tree::planet;
    object->set_position(position);
    object->mass = 5.97e12;
    m_physical.push_back(object);
    m_drawable.push_back(object);
}

// Deconstructor.
tree::layer::game::~game()
{
    std::set<void*> deleted;

    for (uint32_t i = 0; i < m_physical.size(); i++) {
        deleted.insert(m_physical[i]);
        delete m_physical[i];
    }

    for (uint32_t i = 0; i < m_drawable.size(); i++) {
        if (deleted.find(m_drawable[i]) != deleted.end()) {
            deleted.insert(m_drawable[i]);
            delete m_drawable[i];
        }
    }
}

// Return the current timed duration, and restart the timer.
float tree::layer::game::elapsed_time()
{
    std::chrono::duration<float> seconds;
    
    seconds = std::chrono::system_clock::now() - m_timer;
    m_timer = std::chrono::system_clock::now();
    return seconds.count();
}


#include <iostream>
// Execute a game tick.
bool tree::layer::game::execute(std::vector<sf::Event> &events)
{
    // Initialize timer.
    if (!m_executing) {
        m_executing = true;
        m_timer = std::chrono::system_clock::now();
    }

    // Left key pressed. Rotate counter-clockwise.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_player.rotate(false);
    }

    // Right key pressed. Rotate clockwise.
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_player.rotate(true);
    }

    // Up key pressed, thrust.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_player.thrust(true);
    }

    // Down key pressed, brake.
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_player.thrust(false);
    }
 
    // Perform physics.
    for (uint32_t i = 0; i < m_physical.size(); i++) {
        m_physical[i]->pass_time(elapsed_time(), m_physical);
    }

    // Draw player.
    for (uint32_t i = 0; i < m_drawable.size(); i++) {
        m_drawable[i]->draw(m_window, render_states);
    }

    // End this tick.
    return true;
}
