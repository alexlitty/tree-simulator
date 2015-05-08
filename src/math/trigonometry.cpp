#include <math/constant.hpp>
#include <math/trigonometry.hpp>

float tree::math::radians(float degrees)
{
    return (degrees * tree::math::pi) / 180.0f;
}
