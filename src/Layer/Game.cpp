#include <cmath>
#include <set>
#include <tree/Layer/Game.hpp>
#include <tree/Math/Geometry.hpp>
#include <tree/Math/Vector.hpp>
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

    // Initialize player 1.
    sf::Vector2f position(-500.0f, 0.0f);
    //m_player1.setPosition(position);
    m_physical.push_back(&m_player1);
    m_drawable.push_back(&m_player1);

    // Initialize player 2.
    position = sf::Vector2f(500.0f, 0.0f);
    //m_player2.setPosition(position);
    m_physical.push_back(&m_player2);
    m_drawable.push_back(&m_player2);

    // Create a gravity source.
    position.x = -100.0f;
    position.y = 2000.0f;
    tree::Planet *object = new tree::Planet;
    //object->setPosition(position);
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

}

// Return the current timed duration, and restart the timer.
float tree::Layer::Game::elapsedTime()
{
    std::chrono::duration<float> seconds;
    
    seconds = std::chrono::system_clock::now() - m_timer;
    m_timer = std::chrono::system_clock::now();
    return seconds.count();
}

// Execute a Game tick.
bool tree::Layer::Game::execute(std::vector<sf::Event> &events)
{
    // Initialize timer.
    if (!m_executing) {
        m_executing = true;
        m_timer = std::chrono::system_clock::now();
    }

    // Reset.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        return false;
    }

    // Left key pressed. Rotate counter-clockwise.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_player1.rotate(false);
    }

    // Right key pressed. Rotate clockwise.
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_player1.rotate(true);
    }

    // Up key pressed, thrust.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_player1.thrust(true);
    }

    // Down key pressed, brake.
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_player1.thrust(false);
    }

    // Player two rotate counter-clockwise.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        m_player2.rotate(false);
    }

    // Player two rotate clockwise.
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        m_player2.rotate(true);
    }

    // Player two thrust.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        m_player2.thrust(true);
    }

    // Player two brake.
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        m_player2.thrust(false);
    }
 
    // Perform physics.
    float time = elapsedTime();
    for (uint32_t i = 0; i < m_physical.size(); i++) {
    }

    // Get a basic viewport size.
    sf::Vector2f windowSize = static_cast<sf::Vector2f>(m_window.getSize());
    //sf::Vector2f playerDistance = m_player1.getPosition() - m_player2.getPosition();
    float baseViewLength = 100 + 1;
    if (baseViewLength < windowSize.x) {
        baseViewLength = windowSize.x;
    }
    if (baseViewLength < windowSize.y) {
        baseViewLength = windowSize.y;
    }

    // Adjust viewport size to fit window ratio.
    // @@@

    // Apply new viewport size.
    sf::Vector2f viewSize;
    viewSize.x = viewSize.y = baseViewLength;
    viewSize.x = (viewSize.y / windowSize.y) * windowSize.x;
    viewSize.y = (viewSize.x / windowSize.x) * windowSize.y;
    m_view.setSize(viewSize);
    
    // Center viewport.
    //m_view.setCenter(Math::center(m_player1.getPosition(), m_player2.getPosition()));
    m_window.setView(m_view);

    // Adjust backgrounds.
    for (unsigned int i = 0; i < m_background.size(); i++) {
        m_background[i]->setViewTarget(m_view.getCenter());
    }

    // Draw player.
    for (uint32_t i = 0; i < m_drawable.size(); i++) {
        m_drawable[i]->draw(m_window, sf::RenderStates::Default);
    }

    // End this tick.
    return true;
}
