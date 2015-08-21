#include <cmath>
#include <tree/Math/Scalar.hpp>

// Compares the similarity between two floats.
bool tree::similar(float a, float b, float epsilon)
{
    return std::fabs(a - b) < epsilon;
}
