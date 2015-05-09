#ifndef TREESIMULATOR_OBJECT_PLAYER_HPP
#define TREESIMULATOR_OBJECT_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "../component/drawable.hpp"
#include "../component/lifeform.hpp"
#include "../component/physical.hpp"

namespace tree
{
    /**
     * Representation of a player in the game.
     */
    class player : public lifeform, public physical, public tree::drawable
    {
        // Test shape for player.
        sf::RectangleShape m_shape;

        // A friggin hat for the tree
        sf::RectangleShape m_hat;

        // Power of rotational movements.
        float m_rotation_power;

        // Power of non-rotational movements.
        float m_velocity_power;

    public:
        /**
         * Constructor.
         */
        player();

        /**
         * Performs a thrust.
         *
         * If parameter is false, performs a brake.
         */
        void thrust(bool direction);

        /**
         * Perform a rotation.
         *
         * True indicates clockwise, false indicates counter-clockwise.
         */
        void rotate(bool direction);

        /**
         * Draw the player.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif
