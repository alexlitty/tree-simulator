#ifndef TREESIMULATOR_LAYER_HPP
#define TREESIMULATOR_LAYER_HPP

#include <SFML/Window.hpp>
#include <vector>

namespace tree
{
    /**
     * The base of any layer, all of which compose the entire game.
     */
    class layer_t
    {
    public:
        /**
         * Executes this layer.
         *
         * Returns true if this layer should continue existing, false otherwise.
         */
        virtual bool execute(std::vector<sf::Event> &events) = 0;

        /**
         * Deconstructor.
         */
        virtual ~layer_t();
    };
}

#endif
