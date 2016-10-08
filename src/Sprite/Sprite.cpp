#include <tree/Sprite/Sprite.hpp>

// Assigns a texture to this sprite.
void tree::Sprite::setTexture(sf::RenderTexture *newTexture)
{
    this->texture = newTexture;
    this->textureSize = this->texture->getSize();

    this->prepare();
    this->animate();
}

// Gets the texture for this sprite.
const sf::Texture* tree::Sprite::getTexture()
{
    return &this->texture->getTexture();
}

// Animate the sprite.
void tree::Sprite::animate()
{

}

// Converts to texture by returning the underyling texture.
tree::Sprite::operator const sf::Texture*()
{
    return this->getTexture();
}
