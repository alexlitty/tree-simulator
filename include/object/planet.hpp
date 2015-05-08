#ifndef TREESIMULATOR_OBJECT_PLANET_HPP
#define TREESIMULATOR_OBJECT_PLANET_HPP

#include "../component/drawable.hpp"
#include "../component/physical.hpp"

namespace tree
{
    class planet : public physical, public drawable
    {
        // Simple shape for the planet.
        sf::CircleShape m_shape;

    public:

        /**
         * Constructor.
         */
        planet();

        /**
         * Draw the planet.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif
