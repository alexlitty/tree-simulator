#include <cmath>
#include <tree/Gui/Message.hpp>
#include <tree/Layer/Game.hpp>
#include <tree/Math.hpp>
#include <tree/Object/Character/Beaver.hpp>
#include <tree/Object/Planet.hpp>
#include <tree/Physics/Collisions.hpp>
#include <tree/Resource/Font.hpp>
#include <tree/Resource/Shader.hpp>

// Constructor.
tree::Layer::Game::Game(sf::RenderWindow &window)
: m_window(window),
  radar(this->players)
{
    this->players.push_back(new tree::Player);
    this->universe = new tree::Universe(this->players);

    this->debugText.setCharacterSize(18);
    this->debugText.setColor(sf::Color::White);
    this->debugText.setFont(tree::Font::Standard);

    this->updateViews(true);
}

// Destructor.
tree::Layer::Game::~Game()
{
    tree::collisions.clear();

    delete this->universe;
    for (auto player : this->players) {
        delete player;
    }
}

// Updates views.
void tree::Layer::Game::updateViews(bool immediate)
{
    // Center game view on player.
    m_viewGame.setCenter(this->universe->getFocusCenter());

    // Get window resolution.
    sf::Vector2f windowSize(
        static_cast<float>(m_window.getSize().x),
        static_cast<float>(m_window.getSize().y)
    );
    float resolution = windowSize.x / windowSize.y;

    // Set interface view.
    m_viewInterface.setSize(windowSize.x, windowSize.y);
    m_viewInterface.setCenter(windowSize.x / 2.0f, windowSize.y / 2.0f);

    // Realign gui objects.
    radar.setPosition(windowSize.x - (120.0f), 20.0f);

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

    // Perform physics.
    tree::collisions.clear();
    tree::world.Step(1.0 / 120.0f, 20, 20);
    tree::collisions.resolve();

    // Update universe.
    universe->act();

    /*// Perform gravity.
    for (auto gravitySource : m_sta!ge.gravities) {
        for (auto gravityTarget : m_sta!ge.physicals) {
            gravityTarget->applyGravity(gravitySource);
        }
    }*/

    // Set game view.
    this->updateViews();
    m_window.setView(m_viewGame);

    // Disable any shaders.
    m_render_states.shader = nullptr;

    // Draw universe.
    this->universe->draw(m_window, m_render_states);

    // Set interface view.
    m_window.setView(m_viewInterface);

    // Draw gui objects.
    this->radar.draw(m_window, m_render_states);

    // Draw debug mode objects.
    if (tree::debug) {
        Vector debugPosition(0.0f, 0.0f);

        // FPS.
        debugFrames++;
        if (debugFrames >= 1) {
            debugText.setString(
                "FPS: " + std::to_string(
                    static_cast<int>(
                        std::round(
                            debugFrames / debugFramesClock.restart().asSeconds()
                        )
                    )
                )
            );
            debugFrames = 0;
        }
        debugText.setPosition(debugPosition);
        m_window.draw(debugText);

        // Physical objects.
        debugPosition.y += 20.0f;
        debugText.setPosition(debugPosition);
        debugText.setString(
            "Physics objects: "
            + std::to_string(tree::world.GetBodyCount())
        );
        m_window.draw(debugText);

        // Molecules.
        for (unsigned int playerIndex = 0; playerIndex < players.size(); playerIndex++) {
            debugPosition.x = 0.0f;
            debugPosition.y += 40.0f;
            debugText.setPosition(debugPosition);
            debugText.setString("Player #" + std::to_string(playerIndex + 1));
            m_window.draw(debugText);

            for (auto molecule : players[0]->molecules) {
                if (molecule.second) {
                    debugPosition.x = 20.0f;
                    debugPosition.y += 20.0f;
                    debugText.setPosition(debugPosition);

                    debugText.setString(
                        std::to_string(molecule.second)
                        + " "
                        + tree::getMoleculeName(molecule.first)
                    );

                    m_window.draw(debugText);
                }
            }
        }
    }

    // End this frame.
    return true;
}
