#ifndef TREESIMULATOR_SPRITE_SPRITE_HPP
#define TREESIMULATOR_SPRITE_SPRITE_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    /**
     * An advanced texture.
     */
    class Sprite
    {
    protected:

        // Underyling rendering texture.
        sf::RenderTexture *texture = nullptr;
        sf::Vector2u textureSize;

    public:

        /**
         * Assigns a texture to this sprite.
         *
         * Calls prepare() once the texture is assigned.
         */
        void setTexture(sf::RenderTexture *newTexture);

        /**
         * Gets the texture for this sprite.
         */
        const sf::Texture* getTexture();

        /**
         * Prepares a new texture.
         */
        virtual void prepare() = 0;

        /**
         * Animate the sprite.
         */
        virtual void animate();

        /**
         * Convert to texture.
         *
         * Returns the underlying texture.
         */
        operator const sf::Texture*();
    };
}

#endif
