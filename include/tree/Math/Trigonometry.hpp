#ifndef TREESIMULATOR_MATH_TRIG_HPP
#define TREESIMULATOR_MATH_TRIG_HPP

#include <tree/Math/Angle.hpp>
#include <tree/Math/Point.hpp>

namespace tree
{
    /**
     * Calculates the angle made by two points.
     */
    Angle GetAngle(Point &a, Point &b);

    /**
     * @deprecated
     */
    namespace Math
    {
        /**
         * Converts degrees to radians.

         * @deprecated
         */
        float radians(float degrees);

        /**
         * Converts radians to degrees.
         *
         * @deprecated
         */
        float degrees(float radians);
    }
}

#endif
