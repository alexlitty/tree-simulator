#include <tree/Sprite/Hydrogen.hpp>

void tree::sprite::Hydrogen::prepare()
{

}

void tree::sprite::Hydrogen::animate()
{
    this->texture->clear(sf::Color::Cyan);
    this->texture->display();
}
