#ifndef TREESIMULATOR_OBJECT_PLANET_HPP
#define TREESIMULATOR_OBJECT_PLANET_HPP

#include <vector>
#include <tree/Chemistry.hpp>
#include <tree/Component.hpp>
#include <tree/Sprite/Sprite.hpp>

namespace tree
{
    class Planet : virtual public Physical
    {
        // Main fixture for this planet.
        b2Fixture *m_fixture;

        // Sprite for this planet.
        Sprite *sprite;

        // Health of the planet. Lowered when planet crumbles
        unsigned int health = 0;

    public:
        // Elemental composition.
        ElementCollection elements;
        MoleculeCollection molecules;

        /**
         * Constructors.
         */
        Planet(b2Vec2 position);

        /**
         * Destructor.
         */
        ~Planet();

        /**
         * Get the elements that compose this planet.
         */
        ElementCollection getElements();

        /**
         * Gets the normal radius of this planet.
         */
        float getRadius() const;

        /**
         * Gets the density of this planet, influenced by molecules.
         */
        float getMoleculeDensity() const;

        /**
         * Generates this planet based on molecule composition.
         */
        void generate();

        /**
         * Check if the planet can crumble further.
         */
        bool canCrumble() const;

        /**
         * Crumble away from absorption.
         */
        void crumble();

        /**
         * Restores any damage from crumbling.
         */
        void restoreHealth();

        /**
         * Gets a random position on this planet.
         */
        tree::Vector getRandomPosition() const;

        /**
         * Perform actions over time.
         */
        void act();

        /**
         * Draw the planet.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif
