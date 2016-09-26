#include <tree/Math/Misc.hpp>
#include <tree/Math/Vector.hpp>

// Default constructor.
tree::Vector::Vector()
{

}

// Constructor by position.
tree::Vector::Vector(float _x, float _y)
: x(_x),
  y(_y)
{

}

// Constructor by angle and magnitude.
tree::Vector::Vector(Angle angle, float magnitude)
{
    this->x = magnitude * std::cos(angle.radians());
    this->y = magnitude * std::sin(angle.radians());
}

// Conversion constructor, using a SFML vector.
tree::Vector::Vector(const sf::Vector2f &other)
{
    x = other.x;
    y = other.y;
}

// Conversion constructor, using a Box2D vector.
tree::Vector::Vector(const b2Vec2 &other)
{
    x = other.x;
    y = other.y;
}

// Calculates the angle made by this vector alone.
tree::Angle tree::Vector::getAngle() const
{
    tree::Vector zero(0.0f, 0.0f);
    return this->getAngle(zero);
}

// Calculates the angle made by this vector and another vector.
tree::Angle tree::Vector::getAngle(tree::Vector &other) const
{
    float angle;
    Vector sub = (*this) - other;

    // Prevent division by zero.
    if (sub.x == 0 || sub.y == 0) {
        angle = 0.0f;
    }

    // Calculate angle.
    else {
        angle = std::atan2(sub.y, sub.x);
    }

    // Return angle.
    Angle result;
    result.radians(angle);
    return result;
}

// Calculates the magnitude of this vector.
float tree::Vector::getMagnitude() const
{
    return std::sqrt(
        std::pow(this->x, 2) + std::pow(this->y, 2)
    );
}

// Sets the magnitude of this vector.
void tree::Vector::setMagnitude(float magnitude)
{
    float old_magnitude = this->getMagnitude();

    if (this->x != 0.0f) {
        this->x *= magnitude / old_magnitude;
    }

    if (this->y != 0.0f) {
        this->y *= magnitude / old_magnitude;
    }
}



// Extends this vector at an angle.
void tree::Vector::extend(Angle angle, float magnitude)
{
    float a = angle.radians();
    x = magnitude * std::cos(a);
    y = magnitude * std::sin(a);
}

// Finds the distance between this and another vector.
float tree::Vector::distance(tree::Vector other) const
{
    return std::sqrt(
        std::pow(other.x - this->x, 2) + std::pow(other.y - this->y, 2)
    );
}

// Finds the center between this and another vector.
tree::Vector tree::Vector::center(tree::Vector other) const
{
    return Vector(
        (this->x + other.x) / 2,
        (this->y + other.y) / 2
    );
}

// Eases toward another vector.
void tree::Vector::easeToward(tree::Vector &other, float percent)
{
    float x = this->x - other.x;
    float y = this->y - other.y;

    this->x = this->x - (x * percent);
    this->y = this->y - (y * percent);
}

// Calculates the normal of this vector.
tree::Vector tree::Vector::normal() const
{
    tree::Vector zero(0.0f, 0.0f);
    return this->normal(zero);
}

// Calculates the normal of the line made with this vector and another vector.
tree::Vector tree::Vector::normal(tree::Vector& other) const
{
    tree::Vector result(
        other.y - this->y,
        other.x - this->x
    );

    return result;
}

// Calculates the dot product of this and another vector.
float tree::Vector::dot(tree::Vector& other) const
{
    return (this->x * other.x) + (this->y * other.y);
}

// Calculates the cross product of this and another vector.
float tree::Vector::cross(tree::Vector& other) const
{
    return (this->x * other.y) - (this->y * other.x);
}

// Convert to SFML vector.
sf::Vector2f tree::Vector::toDrawable() const
{
    return sf::Vector2f(x, y);
}
tree::Vector::operator sf::Vector2f() const
{
    return this->toDrawable();
}

// Convert to Box2D vector.
b2Vec2 tree::Vector::toPhysical() const
{
    return b2Vec2(x, y);
}
tree::Vector::operator b2Vec2() const
{
    return this->toPhysical();
}

// Subtracts vectors.
tree::Vector& tree::Vector::operator -=(const Vector &rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    return *this;
}

tree::Vector tree::operator -(tree::Vector lhs, const tree::Vector &rhs)
{
    lhs -= rhs;
    return lhs;
}

// Add vectors.
tree::Vector& tree::Vector::operator +=(const tree::Vector &rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

tree::Vector tree::operator +(tree::Vector lhs, const tree::Vector &rhs)
{
    lhs += rhs;
    return lhs;
}

// Multiply vector by an integer.
tree::Vector& tree::Vector::operator *=(const int rhs)
{
    this->x *= rhs;
    this->y *= rhs;
    return *this;
}
tree::Vector tree::operator *(tree::Vector lhs, const int rhs)
{
    lhs *= rhs;
    return lhs;
}

// Multiply vector by a float.
tree::Vector& tree::Vector::operator *=(const float rhs)
{
    this->x *= rhs;
    this->y *= rhs;
    return *this;
}
tree::Vector tree::operator *(tree::Vector lhs, const float rhs)
{
    lhs *= rhs;
    return lhs;
}

// Divide vector by an integer.
tree::Vector& tree::Vector::operator /=(const int rhs)
{
    if (rhs == 0) {
        return *this;
    }

    if (this->x != 0) {
        this->x /= rhs;
    }

    if (this->y != 0) {
        this->y /= rhs;
    }

    return *this;
}
tree::Vector tree::operator /(tree::Vector lhs, const int rhs)
{
    lhs /= rhs;
    return lhs;
}

// Divide vector by a float.
tree::Vector& tree::Vector::operator /=(const float rhs)
{
    if (rhs == 0) {
        return *this;
    }

    if (this->x != 0) {
        this->x /= rhs;
    }

    if (this->y != 0) {
        this->y /= rhs;
    }

    return *this;
}
tree::Vector tree::operator /(tree::Vector lhs, const float rhs)
{
    lhs /= rhs;
    return lhs;
}

// Compare the equality of vectors.
bool tree::operator ==(const tree::Vector &lhs, const tree::Vector &rhs)
{
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

bool tree::operator !=(const tree::Vector &lhs, const tree::Vector &rhs)
{
    return !(lhs == rhs);
}

bool tree::similar(const tree::Vector &lhs, const tree::Vector &rhs, float epsilon)
{
    return tree::similar(lhs.x, rhs.x, epsilon) && tree::similar(lhs.y, rhs.y, epsilon);
}

// Common vectors.
const tree::Vector tree::VectorZero(0.0f, 0.0f);
