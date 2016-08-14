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

    m_positionText.setCharacterSize(18);
    m_positionText.setColor(sf::Color::White);
    m_positionText.setFont(tree::Font::Standard);
    m_positionText.setPosition(0, 22);

    m_velocityText.setCharacterSize(18);
    m_velocityText.setColor(sf::Color::White);
    m_velocityText.setFont(tree::Font::Standard);
    m_velocityText.setPosition(0, 44);

    // Initialize backgrounds.
    for (unsigned int i = 0; i < 10; i++) {

        tree::Background::Stars *bg = new tree::Background::Stars(
            10000, std::pow((i + 2)*1.0f, 2));
        m_stage.add(bg);
        m_background.push_back(bg);
    }

    // Initialize player.
    m_player = new tree::Player();
    m_stage.add(m_player);

    // Create a gravity source.
    /*tree::Planet *planet = new tree::Planet(b2Vec2(25.0f, 0));
    planet->nuggets.add(tree::nugget::rock, 10);
    planet->generate();
    planet->applyTorque(true);
    m_stage.add(planet);

    // Create another gravity source.
    planet = new tree::Planet(
        b2Vec2(25.0f, 15.0f),
        tree::nugget::lava
    );
    b2Vec2 velocity(-5.0f, 0);
    planet->setLinearVelocity(velocity);
    m_stage.add(planet);

    // And another!
    planet = new tree::Planet(b2Vec2(0, 25.0f));
    planet->nuggets.add(tree::nugget::plasma, 20);
    planet->nuggets.add(tree::nugget::lava, 15);
    planet->generate();
    m_stage.add(planet);*/

    // Create beaver.
    /*m_stage.add(
        new tree::character::Beaver(b2Vec2(-50.0f, 0))
    );*/

    this->updateViews(true);

    // Welcome our victim.
    m_stage.add(
        new tree::Message("Welcome to Tree Simulator", MESSAGE::INFO, 240)
    );
}

// Updates views.
void tree::Layer::Game::updateViews(bool immediate)
{
    // Center game view on player.
    m_viewGame.setCenter(m_player->getPixelPosition());

    // Get window resolution.
    sf::Vector2f windowSize(
        static_cast<float>(m_window.getSize().x),
        static_cast<float>(m_window.getSize().y)
    );
    m_stage.windowSize = windowSize;
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
    // Update events, for actors.
    m_stage.events.clear();
    m_stage.events = events;

    // Reset.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        return false;
    }

    // Update universe.
    universe.act(m_stage);

    // Prepare physical objects for more steps.
    for (auto physical : m_stage.physicals) {
        physical->prepare();
    }

    // Perform gravity.
    for (auto gravitySource : m_stage.gravities) {
        for (auto gravityTarget : m_stage.physicals) {
            gravityTarget->applyGravity(gravitySource);
        }
    }

    // Perform physics.
    tree::world.Step(1.0 / 120.0f, 20, 20);

    // Expire objects.
    for (auto expirable : m_stage.expirables) {
        if (expirable->isExpired()) {
            expirable->expire(m_stage);
            m_stage.destroy(expirable);
        }
    }

    // Expire old messages.
    if (m_stage.messages.size() > 1) {
        m_stage.messages.front()->expire();
    }

    // Perform message actions.
    if (m_stage.messages.size() > 0) {
        if (!m_stage.messages.front()->act(m_stage)) {
            m_stage.destroy(m_stage.messages.front());
        }
    }

    // Perform actions.
    for (auto actor : m_stage.actors) {
        actor->act(m_stage);
    }

    // Update the stage.
    m_stage.update();

    // Set game view.
    this->updateViews();
    m_window.setView(m_viewGame);

    // Adjust backgrounds.
    for (unsigned int i = 0; i < m_background.size(); i++) {
        m_background[i]->setViewTarget(m_viewGame.getCenter());
    }

    // Draw objects.
    for (auto drawable : m_stage.drawables) {
        if (!drawable->isGui() && drawable != m_player) {
            drawable->draw(m_window, m_render_states);
        }
    }

    // Disable any shaders.
    m_render_states.shader = nullptr;

    // Draw player.
    m_player->draw(m_window, m_render_states);

    // Set interface view.
    m_window.setView(m_viewInterface);

    // Draw interface.
    for (auto gui : m_stage.guis) {
        gui->draw(m_window, m_render_states);
    }

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

    // Draw position information.
    m_positionText.setString(
        "Position: "
        + std::to_string(
            static_cast<int>(
                std::round(m_player->getPosition().x)
            )
        ) + ", "
        + std::to_string(
            static_cast<int>(
                std::round(m_player->getPosition().y)
            )
        )
    );
    m_window.draw(m_positionText);

    // Draw velocity information.
    m_velocityText.setString(
        "Velocity: "
        + std::to_string(
            static_cast<int>(
                std::round(m_player->getLinearVelocity().getMagnitude())
            )
        )
        + " m/s"
    );
    m_window.draw(m_velocityText);

    // Show messages.
    if (m_stage.messages.size() > 0) {

        // Draw top message.
        m_stage.messages.front()->draw(m_window, m_render_states);
        m_stage.messages.front()->tick();
    }

    // End this tick.
    return true;
}
