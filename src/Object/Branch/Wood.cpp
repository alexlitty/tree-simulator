#include <tree/Object/Branch/Wood.hpp>

// Constructor.
tree::branch::Wood::Wood()
{

}

// Set anchor.
void tree::branch::Wood::setAnchor(sf::Vector2f &a, sf::Vector2f &b)
{
    sf::Vector2f c = a;
    sf::Vector2f d = b;

    // Set top-left and top-right points.
    //float angle = tree::getAngle(c, d);

    shape.setPointCount(4);
    shape.setPoint(0, a);
    shape.setPoint(1, b);
    shape.setPoint(2, c);
    shape.setPoint(3, d);
}

// Draw branch.
void tree::branch::Wood::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(shape);
}
