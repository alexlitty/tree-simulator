#include <tree/Math.hpp>

float tree::IdentityDistribution(float x)
{
    return x;
}

float tree::NormalDistribution(float x)
{
    if (x < 0.5f) {
        return x * 2;
    }

    else {
        return (1.0f - x) * 2;
    }
}
