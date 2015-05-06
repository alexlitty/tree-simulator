#include <layer/game.hpp>
#include <layer/menu.hpp>
#include <resource/font.hpp>
#include <iostream>

// Constructor.
tree::layer::menu::menu(sf::RenderWindow& window)
: m_window(window),
  m_header("Tree Simulator", tree::font::header, 60),
  m_subheader("Press any key to be a tree", tree::font::header, 26),
  blinker(0),
  m_next(nullptr),
  m_fresh(true)
{

}

// Centers the menu items.
void tree::layer::menu::align()
{
    sf::Vector2u size = m_window.getSize();
    sf::Vector2u center(size.x / 2, size.y / 2);
    sf::FloatRect bounds;

    // Align header.
    bounds = m_header.getLocalBounds();
    m_header.setPosition(
        center.x - (bounds.width / 2),
        center.y - (bounds.height / 2)
        );
    m_header.move(0, -88);

    // Align subheader.
    bounds = m_subheader.getLocalBounds();
    m_subheader.setPosition(
        center.x - (bounds.width / 2),
        center.y - (bounds.height / 2)
        );
    m_subheader.move(0, 22);
}

// Returns the next layer to execute.
tree::layer_t* tree::layer::menu::get_next() const
{
    return m_next;
}

// Runs the menu layer.
bool tree::layer::menu::execute(std::vector<sf::Event> &events)
{
    if (m_fresh) {
        m_fresh = false;
        align();
    }
    sf::Color color;

    // Act on events.
    for (unsigned int i = 0; i < events.size(); i++) {

        // Key press.
        if (events[i].type == sf::Event::KeyPressed) {

            // Quit game.
            if (events[i].key.control) {
                m_next = nullptr;
            }
            
            // Start game.
            else {
                m_next = new tree::layer::game(m_window);
            }

            // End menu layer.
            return false;
        }
    }

    // Draw header.
    m_window.draw(m_header);

    // Draw and blink subheader.
    if (blinker > 40) {
        blinker = 0;
    }
    if (blinker++ > 20) {
        color.r = color.g = color.b = 255;
    } else {
        color.r = color.g = color.b = 200;
    }
    m_subheader.setColor(color);
    m_window.draw(m_subheader);
    return true;
}
