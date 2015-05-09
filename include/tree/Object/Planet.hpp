#ifndef TREESIMULATOR_OBJECT_PLANET_HPP
#define TREESIMULATOR_OBJECT_PLANET_HPP

#include "../Component/Drawable.hpp"
#include "../Component/Physical.hpp"

namespace tree
{
    class Planet : public Physical, public Drawable
    {
        // Simple shape for the planet.
        sf::CircleShape m_shape;

    public:

        /**
         * Constructor.
         */
        Planet();

        /**
         * Draw the planet.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif
