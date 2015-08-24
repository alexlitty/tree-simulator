#include <cmath>
#include <tree/Gui/Message.hpp>
#include <tree/Resource/Font.hpp>

// Constructor.
tree::gui::Message::Message(std::string msg, float seconds)
{
    m_isMessage = true;
}

// Check if this message should withdraw.
void tree::gui::Message::actMessage(tree::Stage &stage)
{
    sf::FloatRect bounds = m_wrapper.getGlobalBounds();
    float right = bounds.left + bounds.width;

    // Align message.
    m_messageWrapper.setPosition(
        m_messageWrapper.getPosition().x,
        stage.windowSize.y - 28
    );

    // Message needs to be hidden.
    if (!this->isMessageVisible()) {

        // If not hidden, hide it.
        if (right < 0) {
            m_messageWrapper.move(
                -10.0f * std::abs(right / bounds.width),
                0.0f
            );
        }
    }

    // Message needs to be shown.
    else {

        // Keep message extended.
        if (bounds.left >= -0.5f) {
            m_messageWrapper.setPosition(
                0.0f,
                m_messageWrapper.getPosition().y
            );
        }
        
        // Extend message.
        else if (bounds.left < -0.5f) {
            m_messageWrapper.move(
                10.0f * std::abs(right / bounds.width),
                0.0f
            );
        }
    }

    // Align text.
    m_messageText.setPosition(m_messageWrapper.getPosition());
    return true;
}

// Signal that this message is no longer necessary.
void tree::gui::Message::setMessage(std::string msg, MESSAGE style)
{
    m_messageStringNext = msg;
    m_messageStyleNext = style;
}

// Bring in the next message.
void tree::gui::Message::prepareNextMessage()
{
    m_messageString = m_messageStringNext;
    m_messageStyle = m_messageStyleNext;
}

// Whether this message is visible.
bool tree::gui::isMessageVisible() const
{
    return m_messageVisible;
}

// Draw message.
void tree::gui::Message::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_messageWrapper, states);
    target.draw(m_messageText, states);
}
