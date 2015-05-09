#ifndef TREESIMULATOR_LAYER_MENU_HPP
#define TREESIMULATOR_LAYER_MENU_HPP

#include <SFML/Graphics.hpp>
#include "Type.hpp"

namespace tree
{
    namespace Layer
    {
        class Menu : public Layer::Type
        {
            // Game window.
            sf::RenderWindow& m_window;

            // Text items.
            sf::Text m_header;
            sf::Text m_subheader;

            // Counter for blinking the subheader.
            unsigned char m_blinker;

            // Whether this class has been freshly created.
            bool m_fresh;

        public:
            // Next layer to execute. Undefined until menu ends.
            tree::Layer::Type *next;

            /**
             * Constructor.
             */
            Menu(sf::RenderWindow& window);

            /**
             * Centers the menu items.
             */
            void align();

            /**
             * Runs the menu layer.
             */
            virtual bool execute(std::vector<sf::Event> &events) override;
        };
    }
}

#endif
