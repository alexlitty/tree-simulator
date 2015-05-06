#include <object/player.hpp>

// Constructor.
tree::player::player()
: tree::lifeform::lifeform(10)
{
    m_shape.setSize(sf::Vector2f(10, 20));
    m_shape.setFillColor(sf::Color::Green);
}

#include <iostream>

// Draw the player.
void tree::player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= get_physical_transform();
    target.draw(m_shape, states);
}
