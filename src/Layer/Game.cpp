#include <cmath>
#include <set>
#include <tree/Layer/Game.hpp>
#include <tree/Object/Planet.hpp>

// Constructor.
tree::Layer::Game::Game(sf::RenderWindow &window)
: m_window(window),
  m_executing(false)
{
    // Initialize backgrounds.
    for (unsigned int i = 0; i < 10; i++) {

        tree::Background::Stars *bg = new tree::Background::Stars(
            10000, std::pow((i + 2)*1.0f, 2));
        m_drawable.push_back(bg);
        m_background.push_back(bg);
    }

    // Initialize player.
    sf::Vector2f position(100, 100);
    m_player.setPosition(position);
    m_physical.push_back(&m_player);
    m_drawable.push_back(&m_player);

    // Create a gravity source.
    position.x = position.y = 300;
    tree::Planet* object = new tree::Planet;
    object->setPosition(position);
//    object->mass = 5.97e15;
    object->mass = 0;
    m_physical.push_back(object);
    m_drawable.push_back(object);

    // Initialize viewport.
    sf::Vector2f windowSize(
        static_cast<float>(m_window.getSize().x),
        static_cast<float>(m_window.getSize().y));
    m_view.setCenter(sf::Vector2f(0, 0));
    m_view.setSize(windowSize);
}

// Deconstructor.
tree::Layer::Game::~Game()
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
float tree::Layer::Game::elapsedTime()
{
    std::chrono::duration<float> seconds;
    
    seconds = std::chrono::system_clock::now() - m_timer;
    m_timer = std::chrono::system_clock::now();
    return seconds.count();
}

#include <iostream>

// Execute a Game tick.
bool tree::Layer::Game::execute(std::vector<sf::Event> &events)
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        return false;
    }
 
    // Perform physics.
    for (uint32_t i = 0; i < m_physical.size(); i++) {
        m_physical[i]->passTime(elapsedTime(), m_physical);
    }

    // Adjust viewport.
    m_view.setCenter(m_player.getPosition());
    m_window.setView(m_view);

    // Adjust backgrounds.
    for (unsigned int i = 0; i < m_background.size(); i++) {
        m_background[i]->setViewTarget(m_view.getCenter());
    }

    // Draw player.
    for (uint32_t i = 0; i < m_drawable.size(); i++) {
        m_drawable[i]->draw(m_window, m_render_states);
    }

    for (uint32_t i = 0; i < m_physical.size(); i++) {
        m_physical[i]->boundary.draw(m_window, m_render_states);
        m_window.draw(m_physical[i]->debug, m_render_states);
    }

    // End this tick.
    return true;
}
