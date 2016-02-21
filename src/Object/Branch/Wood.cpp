#include <tree/Object/Branch/Wood.hpp>
#include <tree/Math.hpp>

// @@@
#include <tree/Utility/Debug.hpp>

// Constructor.
tree::branch::Wood::Wood()
{
    shape.setFillColor(sf::Color::White);
}

// Set anchor.
void tree::branch::Wood::setAnchor(sf::Vector2f &a, sf::Vector2f &b)
{
    Point c = a;
    Point d = b;

    // Get angle to extend shape toward.
    Angle angle = c.GetAngle(d);
    pp("Extending angle...");
    std::cout << angle.GetRadians() << std::endl;

    // Set extension points.
    c.Extend(angle, 100.0f);
    d.Extend(angle, 100.0f);

    // Set all shape points.
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
