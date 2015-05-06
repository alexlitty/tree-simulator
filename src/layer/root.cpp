#include <error.hpp>
#include <layer/game.hpp>
#include <layer/menu.hpp>
#include <layer/root.hpp>
#include <resource/font.hpp>
#include <iostream>

/**
 * Constructor.
 */
tree::layer::root::root()
: m_window(sf::VideoMode(800, 600), "Tree Simulator"),
  m_layer(nullptr)
{
    m_window.setVerticalSyncEnabled(true);
    m_menu = new tree::layer::menu(m_window);
}

/**
 * Run Tree Simulator.
 */
bool tree::layer::root::execute(std::vector<sf::Event> &events)
{
    sf::Event event;

    // Font resources.
    if (!tree::font::header.loadFromFile("lobster.otf")) {
        throw tree::error("Header font not found.");
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
                m_menu = new tree::layer::menu(m_window);
            }
        }

        // Or, execute menu layer.
        else {
            if (!m_menu->execute(events)) {
                m_layer = m_menu->get_next();
                
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
