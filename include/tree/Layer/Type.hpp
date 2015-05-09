#ifndef TREESIMULATOR_LAYER_HPP
#define TREESIMULATOR_LAYER_HPP

#include <SFML/Window.hpp>
#include <vector>

namespace tree
{
    namespace Layer
    {
        /**
         * The base of any layer, all of which compose the entire game.
         */
        class Type
        {
        public:
            /**
             * Executes this layer.
             *
             * Returns true if this layer should continue running.
             */
            virtual bool execute(std::vector<sf::Event> &events) = 0;

            /**
             * Deconstructor.
             */
            virtual ~Type();
        };
    }
}

#endif
