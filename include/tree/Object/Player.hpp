#ifndef TREESIMULATOR_OBJECT_PLAYER_HPP
#define TREESIMULATOR_OBJECT_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <tree/Component/Drawable.hpp>
#include <tree/Component/Lifeform.hpp>
#include <tree/Component/Physical.hpp>
#include <tree/Object/Particles.hpp>
#include <tree/Object/Tree/Leaf.hpp>

namespace tree
{
    /**
     * Representation of a Player in the game.
     */
    class Player : public Actor, public Lifeform, public Drawable
    {
        // Test shape for Player.
        sf::RectangleShape m_shape;

        // Test hat for player.
        sf::RectangleShape m_hat;

        // Particles for engine thrust.
        Particles engineParticles;

        // Leaves on the player.
        std::vector<Leaf*> leaves;

    public:

        // Color of test hat.
        sf::Color hatColor;

        /**
         * Constructor and destructor.
         */
        Player();
        ~Player();

        /**
         * Adds a leaf to the player.
         */
        void addLeaf();

        /**
         * Generates the player based on its composition.
         */
        void generate();

        /**
         * Perform actions.
         */
        bool act(tree::Stage &stage) override;

        /**
         * Performs a thrust.
         *
         * If parameter is false, performs a brake.
         */
        void thrust(bool direction);

        /**
         * Draw the player.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif
