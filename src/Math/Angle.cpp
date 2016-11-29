#include <tree/Math/Constant.hpp>
#include <tree/Math/Angle.hpp>

// Default constructor.
tree::Angle::Angle()
{

}

// Sets this angle in radians.
void tree::Angle::radians(float v)
{
    // Reduce a redundant value.
    if (v < 0.0f || v > TWO_PI) {
        v = std::fmod((v + TWO_PI), TWO_PI);
    }

    // Set the internal value.
    this->rads = v;
}

void tree::Angle::addRadians(float v)
{
    this->radians(this->radians() + v);
}

// Sets this angle in degrees.
void tree::Angle::degrees(float v)
{
    this->radians(
        (v * tree::PI) / 180.0f
    );
}

void tree::Angle::addDegrees(float v)
{
    this->degrees(this->degrees() + v);
}

// Retrieves this angle in radians.
float tree::Angle::radians() const
{
    return this->rads;
}

// Retrieves this angle in degrees.
float tree::Angle::degrees() const
{
    return (this->rads * 180.0f) / tree::PI;
}

// Calculates the shortest radian "distance" from this angle to another.
float tree::Angle::distance(tree::Angle other) const
{
    if (*this == other) {
        return 0.0f;
    }

    Angle forward, backward;
    forward.radians(other.radians() - this->radians());
    backward.radians(this->radians() - other.radians());

    if (forward.radians() < backward.radians()) {
        return forward.radians();
    }

    else {
        return -backward.radians();
    }
}

// Eases toward a target angle by an increment.
void tree::Angle::ease(tree::Angle target, tree::Angle increment)
{
    if (*this == target) {
        return;
    }

    // Increment goes beyond target. Set angle to target.
    float distance = this->distance(target);
    if (std::abs(distance) < increment.radians()) {
        *this = target;
        return;
    }

    // Increment clockwise.
    if (distance < 0) {
        *this -= increment;
    }

    // Increment counter-clockwise.
    else {
        *this += increment;
    }
}

// Angle subtraction operators.
tree::Angle tree::operator -(tree::Angle lhs, const tree::Angle& rhs)
{
    lhs -= rhs;
    return lhs;
}

tree::Angle& tree::Angle::operator -=(const tree::Angle& rhs)
{
    this->radians(this->radians() - rhs.radians());
    return *this;
}

// Angle addition operators.
tree::Angle tree::operator +(tree::Angle lhs, const tree::Angle& rhs)
{
    lhs += rhs;
    return lhs;
}

tree::Angle& tree::Angle::operator +=(const tree::Angle& rhs)
{
    this->radians(this->radians() + rhs.radians());
    return *this;
}

// Angle division operators.
tree::Angle tree::operator /(tree::Angle lhs, const unsigned int rhs)
{
    lhs /= rhs;
    return lhs;
}

tree::Angle& tree::Angle::operator /=(const unsigned int rhs)
{
    this->radians(this->radians() / rhs);
    return *this;
}

// Angle equality operators.
bool tree::operator ==(const tree::Angle& lhs, const tree::Angle &rhs)
{
    return lhs.radians() == rhs.radians();
}

bool tree::operator !=(const tree::Angle& lhs, const tree::Angle& rhs)
{
    return !(lhs == rhs);
}
