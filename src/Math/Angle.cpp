#include <tree/Math/Constant.hpp>
#include <tree/Math/Angle.hpp>

// Default constructor.
tree::Angle::Angle()
{

}

// Constructor.
tree::Angle::Angle(float _radians)
{
    SetRadians(_radians);
}

// Sets this angle in radians.
void tree::Angle::SetRadians(float v)
{
    // Reduce a redundant value.
    if (v < 0.0f || v > TWO_PI) {
        v = std::fmod((v + TWO_PI), TWO_PI);
    }

    // Set the internal value.
    radians = v;
}

// Sets this angle in degrees.
void tree::Angle::SetDegrees(float v)
{
    SetRadians(
        (v * 180.0f) / tree::Math::PI
    );
}

// Retrieves this angle in radians.
float tree::Angle::GetRadians() const
{
    return radians;
}

// Retrieves this angle in degrees.
float tree::Angle::GetDegrees() const
{
    return (radians * tree::Math::PI) / 180.0f;
}
