#ifndef TREESIMULATOR_GUI_MESSAGE_HPP
#define TREESIMULATOR_GUI_MESSAGE_HPP

#include <string>
#include <tree/Component.hpp>

namespace tree
{
    /**
     * Styles of messages to be shown to the player.
     */
    enum class MESSAGE {
        INFO,
        BAD,
        SASSY
    };

    /**
     * An object which relays information to the player.
     */
    class Message : virtual public Drawable
    {
        // Ticks remaining to display this message.
        unsigned int m_ticks;

        // Whether this message is visible.
        bool m_messageVisible;

        // Vertical level of this message. 0 for bottom-aligned.
        unsigned int m_level;

        // Drawing shapes.
        sf::RectangleShape m_wrapper;
        sf::RectangleShape m_wrapperShadow;
        sf::Text m_text;

        // Whether this message is a priority to show.
        bool m_prioritized;

    public:

        // Style to display the message in.
        MESSAGE style;

        /**
         * Constructor.
         */
        Message(std::string msg, MESSAGE initStyle, unsigned int ticks, unsigned int level = 0);

        /**
         * Makes this message a priority to show.
         */
        void prioritize();

        /**
         * Whether this message is a priority to show.
         */
        bool isPrioritized() const;

        /**
         * Ages this message.
         */
        void tick();

        /**
         * Immediately expires the message.
         */
        void expire();

        /**
         * Draws the message.
         */
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}

#endif
