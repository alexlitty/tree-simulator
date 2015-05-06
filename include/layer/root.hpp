#ifndef TREESIMULATOR_LAYER_ROOT_HPP
#define TREESIMULATOR_LAYER_ROOT_HPP

#include <exception>
#include <SFML/Graphics.hpp>
#include "menu.hpp"

namespace tree
{
    namespace layer
    {
        class root : public layer_t
        {
            // Window in which Tree Simulator runs in.
            sf::RenderWindow m_window;

            // Menu layer.
            tree::layer::menu *m_menu;

            // Current layer to execute.
            tree::layer_t *m_layer;

        public:
            /**
             * Constructor.
             */
            root();

            /**
             * Run Tree Simulator.
             */
            virtual bool execute(std::vector<sf::Event> &events) override;
        };
    }
}

#endif
