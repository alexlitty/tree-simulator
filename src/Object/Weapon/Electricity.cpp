#include <tree/Object/Weapon/Electricity.hpp>

tree::weapon::Electricity::Electricity(tree::Vector start, tree::Vector end)
: tree::Weapon::Weapon(1)
{
    vertices.setPrimitiveType(sf::LinesStrip);
    vertices.append(start);
    vertices.append(end);
}

void tree::weapon::Electricity::act(std::vector<tree::Vector> &targets)
{

}

void tree::weapon::Electricity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(vertices, states);
}
