#ifndef TREESIMULATOR_COMPONENT_MESSAGE_HPP
#define TREESIMULATOR_COMPONENT_MESSAGE_HPP

#include <string>

namespace tree
{
    /**
     * Styles of messages to be shown to the player.
     */
    enum class MESSAGE {
        INFO,
        ERROR,
        SASSY
    };

    /**
     * An object which relays information to the player.
     */
    class Message
    {
        // Maximum seconds to display this message.
        float m_messageTicks;
        float m_messageTicksNext;

        // String to display.
        std::string m_messageString;
        std::string m_messageStringNext;

        // Message style to display.
        MESSAGE m_messageStyle;
        MESSAGE m_messageStyleNext;

        // Whether this message is visible.
        bool m_messageVisible;

        // Drawing shapes.
        sf::RectangleShape m_messageWrapper;
        sf::Text m_messageText;

    public:

        /**
         * Constructor.
         */
        Message();

        /**
         * Hides and shows messages, and handles new messages.
         */
        void actMessage(tree::Stage &stage);

        /**
         * Sets a new message to be sent to the player.
         *
         * If this is set too quickly, messages may be lost.
         */
        void setMessage(std::string msg, MESSAGE style);

        /**
         * Brings in the next message.
         */
        void prepareNextMessage();

        /**
         * Makes this message appear.
         */
        void setMessageVisible(bool show = true);

        /**
         * Whether this message is visible.
         */
        bool isMessageVisible() const;

        /**
         * Draw this message.
         */
        void drawMessage(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}

#endif
