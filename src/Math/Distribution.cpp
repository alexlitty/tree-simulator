#include <tree/Math.hpp>

float tree::IdentityDistribution(float x)
{
    return x;
}

float tree::NormalDistribution(float x)
{
    return (std::sin(TWO_PI * (x - 0.25)) + 1) / 2;
}

float tree::EaseOutDistribution(float x)
{
    return x * (2 - x);
}
