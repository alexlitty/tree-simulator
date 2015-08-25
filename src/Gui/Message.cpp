#include <cmath>
#include <tree/Gui/Message.hpp>
#include <tree/Resource/Font.hpp>

// Constructor.
tree::Message::Message(std::string msg, tree::MESSAGE initStyle, unsigned int ticks, unsigned int level)
: m_ticks(ticks),
  m_text(msg, tree::Font::Standard, 16),
  style(initStyle)
{
    m_isMessage = true;

    sf::FloatRect bounds = m_text.getLocalBounds();
    sf::Vector2f size(bounds.width, bounds.height);
    size.x += 16;
    size.y += 16;
    m_wrapper.setSize(size);

    m_wrapper.setFillColor(sf::Color::Cyan);
    m_wrapper.setPosition(
        -size.x,
        0
    );

    m_text.setOrigin(8, -8);
}

// Ages the message.
void tree::Message::tick()
{
    if (m_ticks != 0) {
        m_ticks--;
    }
}

// Immediately expires the message.
void tree::Message::expire()
{
    m_ticks = 0;
}

// Shows and hides the message.
#include <iostream>
bool tree::Message::act(tree::Stage &stage)
{
    std::cout << "ACTING" << std::endl;
    sf::FloatRect bounds = m_wrapper.getGlobalBounds();
    float right = bounds.left + bounds.width;

    // Align message.
    m_wrapper.setPosition(
        m_wrapper.getPosition().x,
        (m_level == 0)
            ? stage.windowSize.y - 48
            : m_level * 24
    );

    // Message needs to be hidden.
    if (m_ticks == 0) {

        // Hide it.
        if (right > 0.05f) {
            std::cout << "right: " << right << std::endl;
            m_wrapper.move(
                -25.0f * std::abs((bounds.width -(-bounds.left)) / bounds.width),
                0.0f
            );
        }

        // Fully hidden. Remove it.
        else {
            return false;
        }
    }

    // Message needs to be shown.
    else {
        std::cout << "left: " << bounds.left;

        // Keep message extended.
        if (bounds.left >= -0.5f) {
            m_wrapper.setPosition(
                0.0f,
                m_wrapper.getPosition().y
            );
        }
        
        // Extend message.
        else if (bounds.left < -0.5f) {
            m_wrapper.move(
                25.0f * std::abs((bounds.width - right) / bounds.width),
                0.0f
            );
        }
    }

    // Align text.
    m_text.setPosition(m_wrapper.getPosition());
    return true;
}

// Draws the message.
void tree::Message::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_wrapper, states);
    target.draw(m_text, states);
}
