#ifndef TREESIMULATOR_OBJECT_PLAYER_HPP
#define TREESIMULATOR_OBJECT_PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <tree/Component.hpp>
#include <tree/Object/Particles/PlanetCrumbs.hpp>
#include <tree/Object/Planet.hpp>
#include <tree/Object/Tree/Leaf.hpp>

namespace tree
{
    /**
     * Representation of a Player in the game.
     */
    class Player : public Lifeform
    {
        // Objects that make up the player.
        sf::VertexArray trunk;
        std::vector<sf::VertexArray> branches;
        std::vector<sf::CircleShape> decorativeLeaves;
        std::vector<Leaf*> leaves;

        // Particles for engine thrust.
        Particles engineParticles;

        // Planet that is currently being absorbed.
        tree::Planet *absorptionTarget = nullptr;

        // Crumbs from the planet being absorbed.
        tree::PlanetCrumbs planetCrumbs;

        // Target angle to be rotating towards.
        Angle targetAngle;

    public:

        // Molecular composition.
        ElementCollection elements;
        MoleculeCollection molecules;

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
         * Sets, resets, gets, and checks for an absorption target.
         */
        void setAbsorptionTarget(tree::Planet *target);
        void resetAbsorptionTarget();
        tree::Planet* getAbsorptionTarget() const;
        bool isAbsorbing() const;

        /**
         * Absorbs from the currently targeted planet.
         */
        void absorb();

        /**
         * Finalizes an absorption.
         */
        void takeAbsorptionTarget();

        /**
         * Checks whether the brake is engaged.
         */
        bool isBrakeEngaged() const;

        /**
         * Perform actions.
         */
        void act(std::vector<Lifeform*> &enemies, std::vector<Weapon*> &weapons);

        /**
         * Performs a thrust.
         *
         * If parameter is false, performs a thrust in reverse.
         */
        void thrust(bool direction);

        /**
         * Draw the player.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

    // Collection of players.
    typedef std::vector<Player*> Players;
}

#endif
