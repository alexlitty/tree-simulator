#ifndef TREESIMULATOR_OBJECT_PLANET_HPP
#define TREESIMULATOR_OBJECT_PLANET_HPP

#include <vector>
#include <tree/Component.hpp>
#include <tree/Object/Nugget.hpp>

namespace tree
{
    class Planet : public Physical, public Drawable
    {
        // Simple shape for this planet.
        sf::CircleShape m_shape;

        // Main fixture for this planet.
        b2Fixture *m_fixture;

        // Main texture for this planet.
        sf::RenderTexture *m_texture = nullptr;

    public:

        // Nugget composition of this planet.
        tree::Nuggets m_nuggets;

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
         * Generates this planet. Based on nugget composition.
         */
        void generate();

        /**
         * Draw the planet.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif
