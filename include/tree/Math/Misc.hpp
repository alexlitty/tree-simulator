#ifndef TREESIMULATOR_MATH_MISC_HPP
#define TREESIMULATOR_MATH_MISC_HPP

namespace tree
{
    // Calculates the next power of two.
    unsigned int nextPowerOfTwo(unsigned int value);

    // Compares the similarity of two floats.
    bool similar(float a, float b, float epsilon = 0.001f);
}

#endif
