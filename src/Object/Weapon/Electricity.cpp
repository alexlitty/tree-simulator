#include <tree/Object/Weapon/Electricity.hpp>

tree::weapon::Electricity::Electricity(tree::Vector start, tree::Vector end)
: tree::Expirable::Expirable(1)
{
    Vector magnified;
    Angle angle = start.getAngle(end);
    angle.addDegrees(90);

    vertices.setPrimitiveType(sf::LinesStrip);
    vertices.append(start);
    while (start.easeToward(end, Vector(1.0f, 1.0f))) {
        magnified = start;
        magnified.extend(angle, tree::random(-2.5f, 2.5f));
        vertices.append(magnified);
    }
    vertices.append(end);
}

void tree::weapon::Electricity::act(std::vector<tree::Vector> &targets)
{

}

void tree::weapon::Electricity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(vertices, states);
}
