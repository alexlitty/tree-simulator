#include <cmath>
#include <tree/Gui/Message.hpp>
#include <tree/Layer/Game.hpp>
#include <tree/Math.hpp>
#include <tree/Object/Character/Beaver.hpp>
#include <tree/Object/Planet.hpp>
#include <tree/Resource/Font.hpp>
#include <tree/Resource/Shader.hpp>

// Constructor.
tree::Layer::Game::Game(sf::RenderWindow &window)
: m_window(window)
{
    m_framesText.setCharacterSize(18);
    m_framesText.setColor(sf::Color::White);
    m_framesText.setFont(tree::Font::Standard);

    // Initialize backgrounds.
    for (unsigned int i = 0; i < 10; i++) {

        tree::Background::Stars *bg = new tree::Background::Stars(
            10000, std::pow((i + 2)*1.0f, 2));
        m_background.push_back(bg);
    }

    // Initialize view.
    this->updateViews(true);
}

// Destructor.
tree::Layer::Game::~Game()
{
    //delete m_player;
}

// Updates views.
void tree::Layer::Game::updateViews(bool immediate)
{
    // Center game view on player.
    m_viewGame.setCenter(this->universe.getFocusCenter());

    // Get window resolution.
    sf::Vector2f windowSize(
        static_cast<float>(m_window.getSize().x),
        static_cast<float>(m_window.getSize().y)
    );
    float resolution = windowSize.x / windowSize.y;

    // Set interface view.
    m_viewInterface.setSize(windowSize.x, windowSize.y);
    m_viewInterface.setCenter(windowSize.x / 2.0f, windowSize.y / 2.0f);

    // Get goal size and angle.
    sf::Vector2f goalSize;
    float goalAngle;

    goalSize.y = 200.0f;
    goalAngle = 0.0f;
    goalSize.x = goalSize.y * resolution;

    // Set goal views immediately.
    if (immediate) {
        m_viewGame.setSize(goalSize);
        m_viewGame.setRotation(goalAngle);
    }

    // Set goal views slowly.
    else {

        // Size.
        goalSize -= m_viewGame.getSize();
        goalSize = m_viewGame.getSize() + (goalSize / 10.0f);
        m_viewGame.setSize(goalSize);

        // Angle.
        Angle tempAngle;
        tempAngle.degrees(goalAngle);

        goalAngle = tempAngle.degrees() - m_viewGame.getRotation();

        if (goalAngle > 180.0f) {
            goalAngle = -(360.0f - goalAngle);
        }
        m_viewGame.rotate(goalAngle / 7.0f);
    }
}

// Execute a Game tick.
bool tree::Layer::Game::execute(std::vector<sf::Event> &events)
{
    // Reset.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        return false;
    }

    // Update universe.
    universe.act();

    /*// Perform gravity.
    for (auto gravitySource : m_sta!ge.gravities) {
        for (auto gravityTarget : m_sta!ge.physicals) {
            gravityTarget->applyGravity(gravitySource);
        }
    }*/

    // Perform physics.
    tree::world.Step(1.0 / 120.0f, 20, 20);

    // @@@ expirables? messages?

    // Set game view.
    this->updateViews();
    m_window.setView(m_viewGame);

    // Adjust backgrounds.
    for (unsigned int i = 0; i < m_background.size(); i++) {
        m_background[i]->setViewTarget(m_viewGame.getCenter());
    }

    // Disable any shaders.
    m_render_states.shader = nullptr;

    // Draw universe.
    this->universe.draw(m_window, m_render_states);

    // Set interface view.
    m_window.setView(m_viewInterface);

    // Draw interface.
    // @@@

    // Draw FPS information.
    m_frames++;
    if (m_frames >= 1) {
        m_framesText.setString(
            "FPS: " + std::to_string(
                static_cast<int>(std::round(m_frames / m_framesClock.restart().asSeconds()))
            )
        );
        m_frames = 0;
    }
    m_window.draw(m_framesText);

    // End this frame.
    return true;
}
