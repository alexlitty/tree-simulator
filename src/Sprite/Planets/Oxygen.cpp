#include <tree/Sprite/Planets/Oxygen.hpp>
#include <tree/Math.hpp>

// Constructor.
tree::sprite::OxygenPlanet::OxygenPlanet(float radius)
{
    this->planetShape.setRadius(radius - 1.0f);
    this->planetShape.setPointCount(60);
    tree::centerOrigin(this->planetShape);

    this->planetColor = sf::Color(
        25,
        25,
        25
    );
    this->planetShape.setFillColor(this->planetColor);
    this->planetShape.setOutlineThickness(1.0f);
    this->planetShape.setOutlineColor(sf::Color(200, 200, 200));
}

void tree::sprite::OxygenPlanet::animate()
{

}

void tree::sprite::OxygenPlanet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->planetShape, states);
}
