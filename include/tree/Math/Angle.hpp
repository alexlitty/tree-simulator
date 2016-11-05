#ifndef TREESIMULATOR_MATH_ANGLE_HPP
#define TREESIMULATOR_MATH_ANGLE_HPP

namespace tree
{
    /**
     * An angle, which can be represented in degrees or radians.
     */
    class Angle
    {
        // Internal angle value, in radians.
        float _rads;

    public:

        /**
         * Default constructor.
         */
        Angle();

        /**
         * Sets this angle in radians.
         */
        void radians(float v);
        void addRadians(float v);

        /**
         * Sets this angle in degrees.
         */
        void degrees(float v);
        void addDegrees(float v);

        /**
         * Retrieves this angle in radians.
         */
        float radians() const;

        /**
         * Retrieves this angle in degrees.
         */
        float degrees() const;
    };

    /**
     * Angle operators.
     */
    Angle operator -(Angle left, const Angle& rhs);
    Angle operator +(Angle left, const Angle& rhs);
}

#endif
