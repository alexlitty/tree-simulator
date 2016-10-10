#include <tree/Sprite/Planets/Sun.hpp>
#include <tree/Math.hpp>

// Constructor.
tree::sprite::Sun::Sun(float radius)
{
    this->planetShape.setRadius(radius);
    this->planetShape.setPointCount(60);
    tree::centerOrigin(this->planetShape);

    this->planetColor = sf::Color(
        tree::random(150, 255),
        tree::random(150, 175),
        0
    );
    this->planetShape.setFillColor(this->planetColor);
}

void tree::sprite::Sun::animate()
{

}

void tree::sprite::Sun::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->planetShape, states);
}
