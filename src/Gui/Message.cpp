#include <cmath>
#include <tree/Gui/Message.hpp>
#include <tree/Resource/Font.hpp>

// Constructor.
#include <iostream>
tree::Message::Message(std::string msg, tree::MESSAGE initStyle, unsigned int ticks, unsigned int level)
: m_ticks(ticks),
  m_level(level),
  m_text(msg, tree::Font::Standard, 16),
  m_prioritized(false),
  style(initStyle)
{
    m_isMessage = true;

    sf::FloatRect bounds = m_text.getLocalBounds();
    sf::Vector2f size(bounds.width, bounds.height);
    size.x += 16.0f;
    size.y += 16.0f;
    m_wrapper.setSize(size);

    // Determine wrapper color.
    sf::Color color;
    if (style == MESSAGE::INFO) {
        color = sf::Color(91, 191, 103);
    } else if (style == MESSAGE::BAD) {
        color = sf::Color(217, 13, 40);
    } else {
        color = sf::Color(255, 183, 59);
    }
    m_wrapper.setFillColor(color);
    m_wrapper.setPosition(
        -size.x,
        0
    );

    color.r *= 0.8f;
    color.g *= 0.8f;
    color.b *= 0.8f;
    m_wrapperShadow.setFillColor(color);
    m_wrapperShadow.setOrigin(0, -size.y);
    size.y = 4.0f;
    m_wrapperShadow.setSize(size);
    m_wrapperShadow.setPosition(m_wrapper.getPosition());

    m_text.setOrigin(-8.0f, -5.0f);
}

// Makes this message a priority to show.
void tree::Message::prioritize()
{
    m_prioritized = true;
}

// Whether this message is a priority to show.
bool tree::Message::isPrioritized() const
{
    return m_prioritized;
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
bool tree::Message::act(tree::Stage &stage)
{
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
            m_wrapper.move(
                -75.0f * std::abs((bounds.width -(-bounds.left)) / bounds.width),
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
                150.0f * std::abs((bounds.width - right) / bounds.width),
                0.0f
            );
        }
    }

    // Align text and shadow.
    m_wrapperShadow.setPosition(m_wrapper.getPosition());
    m_text.setPosition(m_wrapper.getPosition());
    return true;
}

// Draws the message.
void tree::Message::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_wrapper, states);
    target.draw(m_wrapperShadow, states);
    target.draw(m_text, states);
}
