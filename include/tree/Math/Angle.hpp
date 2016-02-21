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
        float radians;

    public:

        /**
         * Default constructor.
         */
        Angle();

        /**
         * Constructor.
         */
        Angle(float _radians);

        /**
         * Sets this angle in radians.
         */
        void SetRadians(float v);

        /**
         * Sets this angle in degrees.
         */
        void SetDegrees(float v);

        /**
         * Retrieves this angle in radians.
         */
        float GetRadians() const;

        /**
         * Retrieves this angle in degrees.
         */
        float GetDegrees() const;
    };
}

#endif
