#ifndef TREESIMULATOR_LAYER_ROOT_HPP
#define TREESIMULATOR_LAYER_ROOT_HPP

#include <exception>
#include <SFML/Graphics.hpp>
#include "Menu.hpp"

namespace tree
{
    namespace Layer
    {
        class Root : public Layer::Type
        {
            // Window in which Tree Simulator runs in.
            sf::RenderWindow m_window;

            // Menu layer.
            tree::Layer::Menu *m_menu;

            // Current layer to execute.
            tree::Layer::Type *m_layer;

        public:
            /**
             * Constructor.
             */
            Root();

            /**
             * Run Tree Simulator.
             */
            virtual bool execute(std::vector<sf::Event> &events) override;
        };
    }
}

#endif
