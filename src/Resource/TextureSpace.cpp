#include <tree/Resource/TextureSpace.hpp>

// Constructor.
tree::TextureSpace::TextureSpace(unsigned int width, unsigned int height)
{
    this->texture = new sf::RenderTexture;
    this->texture->create(width, height);
    this->texture->setSmooth(false);
    this->texture->setView(
        sf::View(
            sf::FloatRect(0, 0, width, height)
        )
    );
}

// Constructor.
/*tree::TextureSpace::TextureSpace(sf::RenderTexture *newTexture, sf::Rect newSpace)
: texture(newTexture),
  space(newSpace)
{

}*/

// Destructor.
tree::TextureSpace::~TextureSpace()
{
    delete this->texture;
}

// Assigns a shape to this texture space.
void tree::TextureSpace::assign(sf::Shape &shape)
{
    shape.setTexture(&this->texture->getTexture());
    shape.setTextureRect(this->space);
}

// Creates a new dedicated space based on this space.
/*tree::TextureSpace tree::TextureSpace::partition(unsigned int left, unsigned int top, unsigned int width, unsigned int height)
{
    sf::IntRect rect(left, top, width, height);
    return this->partition(rect);
}

tree::TextureSpace tree::TextureSpace::partition(sf::IntRect &rect)
{
    return TextureSpace(
        this->texture,
        rect
    );
}*/

// Convert to underlying texture.
tree::TextureSpace::operator const sf::Texture*()
{
    return &this->texture->getTexture();
}
