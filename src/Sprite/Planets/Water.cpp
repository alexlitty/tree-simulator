#include <tree/Sprite/Planets/Water.hpp>
#include <tree/Math.hpp>

// Constructor.
tree::sprite::WaterPlanet::WaterPlanet(float radius)
{
    this->planetShape.setRadius(radius - 1.0f);
    this->planetShape.setPointCount(60);
    tree::centerOrigin(this->planetShape);

    this->planetColor = sf::Color(
        tree::random(10, 50),
        tree::random(0, 150),
        tree::random(150, 225)
    );
    this->planetShape.setFillColor(this->planetColor);
}

void tree::sprite::WaterPlanet::animate()
{

}

void tree::sprite::WaterPlanet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->planetShape, states);
}
