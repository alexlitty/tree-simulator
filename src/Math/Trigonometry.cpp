#include <tree/Math/Constant.hpp>
#include <tree/Math/Trigonometry.hpp>

float tree::Math::radians(float degrees)
{
    return (degrees * tree::Math::PI) / 180.0f;
}
