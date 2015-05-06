#ifndef TREESIMULATOR_LAYER_MENU_HPP
#define TREESIMULATOR_LAYER_MENU_HPP

#include <SFML/Graphics.hpp>
#include "../layer.hpp"

namespace tree
{
    namespace layer
    {
        class menu : public layer_t
        {
            // Game window.
            sf::RenderWindow& m_window;

            // 
            sf::Text m_header;
            sf::Text m_subheader;

            // Counter for blinking the subheader.
            unsigned char blinker;

            // Next layer to execute.
            tree::layer_t *m_next;

            // Whether this class has been freshly created.
            bool m_fresh;

        public:
            /**
             * Constructor.
             */
            menu(sf::RenderWindow& window);

            /**
             * Centers the menu items.
             */
            void align();

            /**
             * Returns the next layer to execute.
             */
            tree::layer_t* get_next() const;

            /**
             * Runs the menu layer.
             */
            virtual bool execute(std::vector<sf::Event> &events) override;
        };
    }
}

#endif
