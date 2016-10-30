#ifndef TREESIMULATOR_OBJECT_WORMHOLE_ENTRANCE_HPP
#define TREESIMULATOR_OBJECT_WORMHOLE_ENTRANCE_HPP

#include <tree/Component.hpp>

namespace tree
{
    class WormholeEntrance : public Drawable
    {
        Vector position;
        sf::CircleShape shape;

    public:
        WormholeEntrance(Vector _position);

        /**
         * Whether a vector is within this wormhole's sphere of influence.
         */
        bool canInfluence(Vector other);

        void act();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}

#endif
