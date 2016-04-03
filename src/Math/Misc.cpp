#include <cmath>
#include <tree/Math/Misc.hpp>

// Calculates the next power of two.
unsigned int tree::nextPowerOfTwo(unsigned int value)
{
    --value;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return (value+1) * 2;
}

// Compares the similarity of two floats.
bool tree::similar(float a, float b, float epsilon)
{
    return::fabs(a - b) < epsilon;
}
