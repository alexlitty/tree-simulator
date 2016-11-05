#ifndef TREESIMULATOR_MATH_DISTRIBUTION_HPP
#define TREESIMULATOR_MATH_DISTRIBUTION_HPP

#include <functional>

namespace tree
{
    typedef std::function<float (float)> DistributionFunction;

    float IdentityDistribution(float x);
    float NormalDistribution(float x);
}

#endif
