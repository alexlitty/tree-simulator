#ifndef TREESIMULATOR_OBJECT_PLAYER_HPP
#define TREESIMULATOR_OBJECT_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "../component/lifeform.hpp"
#include "../component/physical.hpp"

namespace tree
{
    /**
     * Representation of a player in the game.
     */
    class player : public lifeform, public physical, public sf::Drawable
    {
        // Test shape for player.
        sf::RectangleShape m_shape;

    public:
        /**
         * Constructor.
         */
        player();

        /**
         * Draw the player.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif
