#include <tree/Layer/Game.hpp>
#include <tree/Layer/Menu.hpp>
#include <tree/Resource/Font.hpp>

// Constructor.
tree::Layer::Menu::Menu(sf::RenderWindow& window)
: m_window(window),
  m_header("Tree Simulator", tree::Font::Header, 60),
  m_subheader("Press any key to be a tree", tree::Font::Header, 26),
  m_version("Alpha Release - \"Hat Simulator\"", tree::Font::Header, 26),
  m_blinker(0),
  m_fresh(true),
  next(nullptr)
{
    m_window.setView(m_window.getDefaultView());
}

// Centers the menu items.
void tree::Layer::Menu::align()
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

    // Align version.
    bounds = m_version.getLocalBounds();
    m_version.setPosition(
        center.x - (bounds.width / 2),
        size.y - (bounds.height * 2)
    );
}

// Runs the menu layer.
bool tree::Layer::Menu::execute(std::vector<sf::Event> &events)
{
    align();
    next = nullptr;
    sf::Color color;

    // Act on events.
    for (unsigned int i = 0; i < events.size(); i++) {

        // Key press.
        if (events[i].type == sf::Event::KeyPressed) {

            // Quit game.
            if (events[i].key.control) {
                next = nullptr;
            }
            
            // Start game.
            else {
                next = new tree::Layer::Game(m_window);
            }

            // End menu layer.
            return false;
        }
    }

    // Draw static text.
    m_window.draw(m_header);
    m_window.draw(m_version);

    // Draw and blink subheader.
    if (m_blinker > 40) {
        m_blinker = 0;
    }
    if (m_blinker++ > 20) {
        color.r = color.g = color.b = 255;
    } else {
        color.r = color.g = color.b = 200;
    }
    m_subheader.setColor(color);
    m_window.draw(m_subheader);

    return true;
}
