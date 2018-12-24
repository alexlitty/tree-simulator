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
  introMinigame(nullptr),
  universe(nullptr),
  radar(this->players),
  welcomeTextMessage("Welcome to", tree::Font::Header, 26),
  welcomeTextLogo("Tree Simulator", tree::Font::Header, 60),
  welcomeTicker(300)
{
    this->players.push_back(new tree::Player);

    this->debugText.setCharacterSize(18);
    this->debugText.setColor(sf::Color::White);
    this->debugText.setFont(tree::Font::Standard);
}

// Destructor.
tree::Layer::Game::~Game()
{
    tree::collisions.clear();

    delete this->universe;
    for (auto player : this->players) {
        delete player;
    }
    delete this->introMinigame;
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
    this->welcomeTextMessage.setPosition(50.0f, windowSize.y - 140.0f);
    this->welcomeTextLogo.setPosition(50.0f, windowSize.y - 110.0f);
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
        goalSize = m_viewGame.getSize() + (goalSize / 20.0f);
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
    tree::physics::world.Step(1.0 / 120.0f, 20, 20);
    tree::collisions.resolve();

    // Start the game.
    if (!this->universe && !this->introMinigame) {
        this->introMinigame = new Layer::IntroMinigame(this->m_window, this->players);
    }

    // Play intro minigame.
    if (this->introMinigame) {
        if (!this->introMinigame->execute(events)) {
            this->m_viewGame = this->introMinigame->gameView;
            delete this->introMinigame;
            this->introMinigame = nullptr;

            this->universe = new tree::Universe(this->players);
        }
        
        else {
            this->introMinigame->draw();
        }

        return true;
    }

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

    // Draw and update welcome text.
    if (!this->welcomeTicker.tick()) {
        float welcomePercent = this->welcomeTicker.percent();

        sf::Color welcomeTextColor = sf::Color::White;
        if (welcomePercent < 0.25f) {
            welcomeTextColor.a = 255 * (welcomePercent * 4.0f);
        } else if (welcomePercent > 0.75f) {
            welcomeTextColor.a = 255 * ((1.0f - welcomePercent) * 4.0f);
        }
        this->welcomeTextMessage.setColor(welcomeTextColor);
        this->welcomeTextLogo.setColor(welcomeTextColor);

        m_window.draw(this->welcomeTextMessage, m_render_states);
        m_window.draw(this->welcomeTextLogo, m_render_states);
    }

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
            + std::to_string(tree::physics::world.GetBodyCount())
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
