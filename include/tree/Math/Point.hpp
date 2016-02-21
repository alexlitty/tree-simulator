#ifndef TREESIMULATOR_MATH_POINT_HPP
#define TREESIMULATOR_MATH_POINT_HPP

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

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
        Point(sf::Vector2f &other);
        Point(b2Vec2 &other);

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
