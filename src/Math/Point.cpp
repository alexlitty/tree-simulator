#include <tree/Math/Point.hpp>

// Default constructor.
tree::Point::Point()
{

}

// Constructor.
tree::Point::Point(float _x, float _y)
: x(_x),
  y(_y)
{

}

// Conversion constructor, using a SFML vector.
tree::Point::Point(const sf::Vector2f &other)
{
    x = other.x;
    y = other.y;
}

// Conversion constructor, using a Box2D vector.
tree::Point::Point(const b2Vec2 &other)
{
    x = other.x;
    y = other.y;
}

// Calculates the angle made by this point and another point.
tree::Angle tree::Point::GetAngle(tree::Point &other) const
{
    Point sub = (*this) - other;

    // Prevent division by zero.
    if (sub.x == 0 || sub.y == 0) {
        return 0.0f;
    }

    // Return angle.
    return std::atan2(sub.y, sub.x);
}

// Extends this point at an angle.
void tree::Point::Extend(Angle angle, float magnitude)
{
    float a = angle.GetRadians();
    x = magnitude * std::cos(a);
    y = magnitude * std::sin(a);
}

// Convert to SFML vector.
tree::Point::operator sf::Vector2f() const
{
    return sf::Vector2f(x, y);
}

// Convert to Box2D vector.
tree::Point::operator b2Vec2() const
{
    return b2Vec2(x, y);
}

// Subtracts points.
tree::Point& tree::Point::operator -=(const Point &rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;

    return *this;
}

tree::Point tree::operator -(tree::Point lhs, const tree::Point &rhs)
{
    lhs -= rhs;
    return lhs;
}
