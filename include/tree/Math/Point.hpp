#ifndef TREESIMULATOR_MATH_POINT_HPP
#define TREESIMULATOR_MATH_POINT_HPP

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include <tree/Math/Angle.hpp>

namespace tree
{
    struct Point
    {
        float x;
        float y;

        /**
         * Default constructor.
         */
        Point();

        /**
         * Constructor.
         */
        Point(float _x, float _y);

        /**
         * Conversion constructors.
         */
        Point(const sf::Vector2f &other);
        Point(const b2Vec2 &other);

        /**
         * Calculates the angle made by this point and another point.
         */
        Angle GetAngle(Point &other) const;

        /**
         * Extends this point at an angle.
         */
        void Extend(Angle angle, float magnitude);

        /**
         * Convert to SFML vector.
         */
        operator sf::Vector2f() const;

        /**
         * Convert to Box2D vector.
         */
        operator b2Vec2() const;

        /**
         * Subtracts points.
         */
        Point& operator -=(const Point &rhs);
    };

    /**
     * Subtract points.
     */
    Point operator -(Point lhs, const Point &rhs);
}

#endif
