#ifndef TREESIMULATOR_SPRITE_SPRITE_HPP
#define TREESIMULATOR_SPRITE_SPRITE_HPP

#include <tree/Component.hpp>

namespace tree
{
    /**
     * An animated drawable.
     */
    class Sprite : public Drawable
    {
    public:
        /**
         * Animates the sprite.
         */
        virtual void animate();

        /**
         * Draws the sprite.
         */
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    };
}

#endif
