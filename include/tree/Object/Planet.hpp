#ifndef TREESIMULATOR_OBJECT_PLANET_HPP
#define TREESIMULATOR_OBJECT_PLANET_HPP

#include <vector>
#include <tree/Component.hpp>

namespace tree
{
    class Planet
    : public Drawable,
      public Nuggetable
    {
        // Simple shape for this planet.
        sf::CircleShape m_shape;

        // Highlighting shape.
        sf::CircleShape m_highlight;

        // Main fixture for this planet.
        b2Fixture *m_fixture;

        // Main texture for this planet.
        sf::RenderTexture *m_texture = nullptr;

    public:

        /**
         * Constructors.
         */
        Planet(b2Vec2 position);
        Planet(b2Vec2 position, tree::nugget initialNugget);

        /**
         * Destructor.
         */
        ~Planet();

        /**
         * Gets the normal radius of this planet.
         */
        float getRadius() const;

        /**
         * Gets the density of this planet, influenced by nuggets.
         */
        float getNuggetDensity() const;

        /**
         * Receives a new nugget.
         */
        void receiveNugget(tree::nugget nugget) override;

        /**
         * Generates this planet. Based on nugget composition.
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
        void uncrumble();

        /**
         * Draw the planet.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif
