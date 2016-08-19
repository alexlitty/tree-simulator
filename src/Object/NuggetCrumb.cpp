#include <tree/Object/NuggetCrumb.hpp>

// Constructor.
tree::NuggetCrumb::NuggetCrumb()
{
    this->shape.setPointCount(5);
    this->shape.setRadius(0.5f);
    this->shape.setFillColor(sf::Color::White);
}

// Moves the crumb towards a vector.
void tree::NuggetCrumb::moveToward(tree::Vector vector)
{
    tree::Vector position = this->shape.getPosition();
    position.easeToward(vector);
    this->shape.setPosition(position);
}

// Draw this crumb.
void tree::NuggetCrumb::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->shape, states);
}
