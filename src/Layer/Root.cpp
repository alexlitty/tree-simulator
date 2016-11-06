#include <ctime>

#include <tree/Engine/Error.hpp>
#include <tree/Layer/Game.hpp>
#include <tree/Layer/Menu.hpp>
#include <tree/Layer/Root.hpp>
#include <tree/Math/Random.hpp>
#include <tree/Resource/Font.hpp>
#include <tree/Resource/Shader.hpp>

/**
 * Constructor.
 */
tree::Layer::Root::Root()
: m_window(sf::VideoMode(1300, 700), "Tree Simulator", 0, sf::ContextSettings(0, 0, 3)),
  m_layer(nullptr)
{
    m_window.setVerticalSyncEnabled(true);
    m_menu = new tree::Layer::Menu(m_window);

    // Seed random number generator.
    tree::seedRandom(static_cast<unsigned int>(std::time(0)));
}

/**
 * Run Tree Simulator.
 */
bool tree::Layer::Root::execute(std::vector<sf::Event> &events)
{
    sf::Event event;

    // Font resources.
    if (!tree::Font::Header.loadFromFile("lobster.otf")) {
        throw tree::Error("Could not load header font.");
    }
    if (!tree::Font::Standard.loadFromFile("glacial.otf")) {
        throw tree::Error("Could not load standard font.");
    }

    // Shader resources.
    if (!tree::Shader::ForceAlpha.loadFromFile("ForceAlpha.shader", sf::Shader::Vertex)) {
        throw tree::Error("Could not load alpha shader.");
    }
    if (!tree::Shader::Fisheye.loadFromFile("Fisheye.shader", sf::Shader::Fragment)) {
        throw tree::Error("Could not load fisheye shader.");
    }
    tree::Shader::Fisheye.setParameter("texture", sf::Shader::CurrentTexture);

    if (!tree::Shader::NoiseSimple.loadFromFile("NoiseSimple.glsl", sf::Shader::Fragment)) {
        throw tree::Error("Could not load simple noise shader.");
    }

    // Main game loop.
    while (m_window.isOpen()) {

        // Check for quit-game conditions.
        if (m_menu == nullptr && m_layer == nullptr) {
            m_window.close();
            return false;
        }

        // Collect events.
        events.clear();
        while (m_window.pollEvent(event)) {
            // Check for close window event.
            if (event.type == sf::Event::Closed) {
                if (m_layer != nullptr) {
                    delete m_layer;
                    m_layer = nullptr;
                }
                if (m_menu != nullptr) {
                    delete m_menu;
                    m_menu = nullptr;
                }
                break;
            }

            events.push_back(event);
        }

        // Clear window for drawing.
        m_window.clear();

        // Execute top-most layer.
        if (m_layer != nullptr) {
            if (!m_layer->execute(events)) {

                // Clear top-most layer.
                delete m_layer;
                m_layer = nullptr;

                // Start a new menu instance.
                m_menu = new tree::Layer::Menu(m_window);
            }
        }

        // Or, execute menu layer.
        else {
            if (m_menu != nullptr && !m_menu->execute(events)) {
                m_layer = m_menu->next;
                
                // Remove this menu instance.
                delete m_menu;
                m_menu = nullptr;

                // Push to end the game, if quitting.
                if (m_layer == nullptr) {
                    continue;
                }
            }
        }

        // Display drawn objects.
        m_window.display();
    }
    return false;
}
