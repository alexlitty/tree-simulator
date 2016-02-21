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
tree::Point::Point(sf::Vector2f &other)
{
    x = other.x;
    y = other.y;
}

// Conversion constructor, using a Box2D vector.
tree::Point::Point(b2Vec2 &other)
{
    x = other.x;
    y = other.y;
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
