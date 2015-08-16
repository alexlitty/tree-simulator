#include <cmath>
#include <set>
#include <tree/Layer/Game.hpp>
#include <tree/Math/Constant.hpp>
#include <tree/Math/Geometry.hpp>
#include <tree/Math/Vector.hpp>
#include <tree/Object/Planet.hpp>
#include <tree/Physics/Collisions.hpp>

// Constructor.
tree::Layer::Game::Game(sf::RenderWindow &window)
: m_window(window),
  m_executing(false)
{
    // Initialize backgrounds.
    for (unsigned int i = 0; i < 10; i++) {

        tree::Background::Stars *bg = new tree::Background::Stars(
            10000, std::pow((i + 2)*1.0f, 2));
        //m_drawable.push_back(bg);
        //m_background.push_back(bg);
    }

    // Initialize player 1.
    //b2Vec2 initPos = b2Vec2(1.0f, -0.3f);
    //m_player1.setPosition(initPos);
    m_gravity.push_back(&m_player1);
    m_drawable.push_back(&m_player1);

    // Create a gravity source.
    tree::Planet *object = new tree::Planet(50.0f, 3E10, b2Vec2(200.0f, 0));
    m_gravity.push_back(object);
    m_drawable.push_back(object);

    // Create another gravity source.
    object = new tree::Planet(10.0f, 3E10, b2Vec2(200.0f, 100.0f));
    b2Vec2 velocity(-150.0f, 0);
    object->setLinearVelocity(velocity);
    m_gravity.push_back(object);
    m_drawable.push_back(object);

    // Initialize viewport resolution.
    sf::Vector2f windowSize(
        static_cast<float>(m_window.getSize().x),
        static_cast<float>(m_window.getSize().y));
    float resolution = windowSize.x / windowSize.y;
    m_view.setCenter(sf::Vector2f(0, 0));
    m_view.setSize(tree::pixels(200.0f * resolution), tree::pixels(200.0f));
}

// Deconstructor.
tree::Layer::Game::~Game()
{
    tree::collisions.clear();

    for (auto physical : m_gravity) {
        delete physical;
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

    // Perform gravity.
    for (auto gravitySource : m_gravity) {
        for (auto gravityTarget : m_gravity) {
            gravityTarget->applyGravity(*gravitySource);
        }
    }

    // Perform physics.
    tree::world.Step(1.0 / 120.0f, 8, 3);

    // Update viewport.
    m_view.setCenter(m_player1.getPixelPosition());
    m_window.setView(m_view);

    // Adjust backgrounds.
    for (unsigned int i = 0; i < m_background.size(); i++) {
        m_background[i]->setViewTarget(m_view.getCenter());
    }

    // Draw objects.
    for (uint32_t i = 0; i < m_drawable.size(); i++) {
        m_drawable[i]->draw(m_window, m_render_states);
    }

    // End this tick.
    return true;
}
