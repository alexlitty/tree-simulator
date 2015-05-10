#ifndef TREESIMULATOR_OBJECT_PLAYER_HPP
#define TREESIMULATOR_OBJECT_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "../Component/Drawable.hpp"
#include "../Component/Lifeform.hpp"
#include "../Component/Physical.hpp"

namespace tree
{
    /**
     * Representation of a Player in the game.
     */
    class Player : public Lifeform, public Physical, public Drawable
    {
        // Test shape for Player.
        sf::RectangleShape m_shape;

        // Power of rotational movements.
        float m_rotationPower;

        // Power of non-rotational movements.
        float m_velocityPower;

    public:
        /**
         * Constructor.
         */
        Player();

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
