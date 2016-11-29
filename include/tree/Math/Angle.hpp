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
        float rads;

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

        /**
         * Calculates the shorted radian "distance" from this angle to another.
         *
         * Range is -PI to PI, inclusive.
         *
         * If the result is negative, the other angle is closest to this angle
         * by clockwise rotation. If positive, counter-clockwise.
         */
        float distance(Angle other) const;

        /**
         * Eases towards a target angle by an increment.
         *
         * Increment will be applied in either clockwise or counter-clockwise
         * directions, whichever is closer to the target.
         */
        void ease(Angle target, Angle increment);

        /**
         * Mathematical operators.
         */
        Angle& operator -=(const Angle& rhs);
        Angle& operator +=(const Angle& rhs);
        Angle& operator /=(const unsigned int rhs);
    };

    /**
     * Mathematical operators.
     */
    Angle operator -(Angle lhs, const Angle& rhs);
    Angle operator +(Angle lhs, const Angle& rhs);
    Angle operator /(Angle lhs, const unsigned int rhs);

    /**
     * Logical operators.
     */
    bool operator ==(const Angle& lhs, const Angle& rhs);
    bool operator !=(const Angle& lhs, const Angle& rhs);
}

#endif
