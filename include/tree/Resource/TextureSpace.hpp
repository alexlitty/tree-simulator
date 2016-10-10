#ifndef TREESIMULATOR_RESOURCE_TEXTURE_HPP
#define TREESIMULATOR_RESOURCE_TEXTURE_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    /**
     * Dedicated space on a true texture.
     *
     * @todo - Uses a whole new texture for now. Improve this later.
     */
    struct TextureSpace
    {
        sf::RenderTexture *texture;
        sf::IntRect space;

        /**
         * Constructor.
         */
        TextureSpace(unsigned int width, unsigned int height);

        /**
         * Constructor.
         *
         * @ Not ready for this yet.
         */
        //TextureSpace(sf::RenderTexture *newTexture, sf::Rect newSpace);

        /**
         * Destructor.
         */
        ~TextureSpace();

        /**
         * Assigns a shape to this texture space.
         */
        void assign(sf::Shape &shape);

        /**
         * Creates a new dedicated space based on this space.
         */
        //TextureSpace partition(unsigned int left, unsigned int top, unsigned int width, unsigned int height);
        //TextureSpace partition(sf::IntRect &rect);

        /**
         * Convert to underlying texture.
         */
        operator const sf::Texture*();
    };
}

#endif
