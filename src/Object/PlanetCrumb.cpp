#include <tree/Object/PlanetCrumb.hpp>

// Constructor.
tree::PlanetCrumb::PlanetCrumb()
{
    this->shape.setPointCount(5);
    this->shape.setRadius(0.5f);
    this->shape.setFillColor(sf::Color::White);
}

// Draw this crumb.
void tree::PlanetCrumb::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->shape, states);
}
