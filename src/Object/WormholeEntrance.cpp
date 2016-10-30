#include <tree/Object/WormholeEntrance.hpp>

tree::WormholeEntrance::WormholeEntrance(tree::Vector _position)
: position(_position)
{
    this->shape.setRadius(10.0f);
    this->shape.setOutlineThickness(1.0f);
    this->shape.setOutlineColor(sf::Color::Green);
    this->shape.setFillColor(sf::Color::Cyan);

    tree::centerOrigin(this->shape);
    this->shape.setPosition(position);
}

bool tree::WormholeEntrance::canInfluence(Vector other)
{
    return this->position.isNear(other, 10.0f);
}

void tree::WormholeEntrance::act()
{

}

void tree::WormholeEntrance::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->shape, states);
}
