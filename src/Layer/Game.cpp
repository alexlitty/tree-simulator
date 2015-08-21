#include <cmath>
#include <tree/Layer/Game.hpp>
#include <tree/Math/Constant.hpp>
#include <tree/Math/Geometry.hpp>
#include <tree/Math/Vector.hpp>
#include <tree/Object/Character/Beaver.hpp>
#include <tree/Object/Planet.hpp>
#include <tree/Physics/Collisions.hpp>
#include <tree/Resource/Font.hpp>
#include <tree/Utility/Collection.hpp>

// @@

// Constructor.
tree::Layer::Game::Game(sf::RenderWindow &window)
: m_window(window)
{
    m_framesText.setCharacterSize(18);
    m_framesText.setColor(sf::Color::White);
    m_framesText.setFont(tree::Font::Header);

    // Initialize backgrounds.
    for (unsigned int i = 0; i < 10; i++) {

        //tree::Background::Stars *bg = new tree::Background::Stars(
            //10000, std::pow((i + 2)*1.0f, 2));
        //m_drawable.push_back(bg);
        //m_background.push_back(bg);
    }

    // Initialize player.
    m_player = new tree::Player();
    m_objects.push_back(m_player);

    // Create a gravity source.
    tree::Planet *planet = new tree::Planet(50.0f, 3E10, b2Vec2(200.0f, 0));
    m_objects.push_back(planet);

    // Create another gravity source.
    planet = new tree::Planet(10.0f, 3E10, b2Vec2(200.0f, 100.0f));
    b2Vec2 velocity(-150.0f, 0);
    planet->setLinearVelocity(velocity);
    m_objects.push_back(planet);

    // Create beaver.
    m_objects.push_back(
        new tree::character::Beaver(b2Vec2(-50.0f, 0))
    );

    // Initialize viewport resolution.
    sf::Vector2f windowSize(
        static_cast<float>(m_window.getSize().x),
        static_cast<float>(m_window.getSize().y));
    float resolution = windowSize.x / windowSize.y;
    m_viewGame.setCenter(sf::Vector2f(0, 0));
    m_viewGame.setSize(tree::pixels(200.0f * resolution), tree::pixels(200.0f));
}

// Deconstructor.
tree::Layer::Game::~Game()
{
    // Cleanup physics.
    tree::collisions.clear();

    // Collect objects to destroy.
    for (auto drawable : m_drawable) {
        m_objectsDestroy.insert(drawable);
    }
    for (auto physical : m_physical) {
        m_objectsDestroy.insert(physical);
    }
    for (auto actor : m_actor) {
        m_objectsDestroy.insert(actor);
    }
    for (auto expirable : m_expirable) {
        m_objectsDestroy.insert(expirable);
    }
    for (auto object : m_objects) {
        m_objectsDestroy.insert(object);
    }

    m_objects.clear();
    updateObjects();
}

// Update object collections.
void tree::Layer::Game::updateObjects()
{
    // Add new objects.
    for (auto object : m_objects) {

        if (object->isDrawable()) {
            m_drawable.push_back(
                dynamic_cast<tree::Drawable*>(object)
            );
        }

        if (object->isPhysical()) {
            m_physical.push_back(
                dynamic_cast<tree::Physical*>(object)
            );
        }

        if (object->isActor()) {
            m_actor.push_back(
                dynamic_cast<tree::Actor*>(object)
            );
        }

        if (object->isExpirable()) {
            m_expirable.push_back(
                dynamic_cast<tree::Expirable*>(object)
            );
        }
    }
    m_objects.clear();

    // Destroy objects.
    for (auto object : m_objectsDestroy) {

        // Clear from drawable objects.
        tree::remove(
            m_drawable,
            dynamic_cast<tree::Drawable*>(object)
        );

        // Clear from physical objects.
        tree::remove(
            m_physical,
            dynamic_cast<tree::Physical*>(object)
        );

        // Clear from actor objects.
        tree::remove(
            m_actor,
            dynamic_cast<tree::Actor*>(object)
        );

        // Clear from expirable objects.
        tree::remove(
            m_expirable,
            dynamic_cast<tree::Expirable*>(object)
        );
        
        // Destroy object.
        delete object;
    }
    m_objectsDestroy.clear();
}

// Execute a Game tick.
bool tree::Layer::Game::execute(std::vector<sf::Event> &events)
{
    // Reset.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        return false;
    }

    // Left key pressed. Rotate counter-clockwise.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_player->rotate(false);
    }

    // Right key pressed. Rotate clockwise.
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_player->rotate(true);
    }

    // Up key pressed, thrust.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_player->thrust(true);
    }

    // Down key pressed, brake.
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_player->thrust(false);
    }

    // Space key is pressed, shoot.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        m_player->toggleShooting(true);
    } else {
        m_player->toggleShooting(false);
    }

    // Expire objects.
    for (auto expirable : m_expirable) {
        if (expirable->isExpired()) {
            expirable->expire(m_objects);
            m_objectsDestroy.insert(expirable);
        }
    }
    updateObjects();

    // Perform actions.
    for (auto actor : m_actor) {
        if (!actor->act(m_objects)) {
            m_objectsDestroy.insert(actor);
        }
    }
    updateObjects();

    // Perform gravity.
    for (auto gravitySource : m_physical) {
        for (auto gravityTarget : m_physical) {
            gravityTarget->applyGravity(gravitySource);
        }
    }

    // Perform physics.
    tree::world.Step(1.0 / 120.0f, 20, 20);

    // Set game view.
    m_viewGame.setCenter(m_player->getPixelPosition());
    m_window.setView(m_viewGame);

    // Adjust backgrounds.
    for (unsigned int i = 0; i < m_background.size(); i++) {
        m_background[i]->setViewTarget(m_viewGame.getCenter());
    }

    // Draw objects.
    for (uint32_t i = 0; i < m_drawable.size(); i++) {
        m_drawable[i]->draw(m_window, m_render_states);
    }

    // Set interface view.
    m_window.setView(m_viewInterface);

    // Draw FPS information.
    m_frames++;
    if (m_frames >= 5) {
        m_framesText.setString(
            "FPS - " + std::to_string(
                static_cast<int>(std::round(m_frames / m_framesClock.restart().asSeconds()))
            )
        );
        m_frames = 0;
    }
    m_window.draw(m_framesText);

    // End this tick.
    return true;
}
