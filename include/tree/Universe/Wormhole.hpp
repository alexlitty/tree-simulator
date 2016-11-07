#ifndef TREESIMULATOR_UNIVERSE_WORMHOLE_HPP
#define TREESIMULATOR_UNIVERSE_WORMHOLE_HPP

#include <tree/Component.hpp>

namespace tree
{
    class Wormhole : public Drawable
    {
        sf::CircleShape test;

    public:
        Wormhole();

        bool act();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}

#endif
