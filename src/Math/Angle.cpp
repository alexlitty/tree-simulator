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
    _rads = v;
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
    return _rads;
}

// Retrieves this angle in degrees.
float tree::Angle::degrees() const
{
    return (_rads * 180.0f) / tree::PI;
}

// Angle subtraction operator.
tree::Angle tree::operator -(tree::Angle lhs, const tree::Angle& rhs)
{
    lhs.radians(lhs.radians() - rhs.radians());
    return lhs;
}

// Angle addition operator.
tree::Angle tree::operator +(tree::Angle lhs, const tree::Angle& rhs)
{
    lhs.radians(lhs.radians() + rhs.radians());
    return lhs;
}
