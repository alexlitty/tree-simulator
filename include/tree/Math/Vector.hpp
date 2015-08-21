#ifndef TREESIMULATOR_MATH_VECTOR
#define TREESIMULATOR_MATH_VECTOR

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

namespace tree
{
    /**
     * Reduces an angle.
     */
    float angle(float a);

    /**
     * Finds the angle between two points.
     */
    float getAngle(b2Vec2 point, b2Vec2 target);

    /**
     * Calculates the dot product of two vectors.
     */
    float dot(b2Vec2& left, b2Vec2& right);

    namespace Math
    {
        /**
         * Converts drawing vectors and physical vectors.
         */
        sf::Vector2f vector(const b2Vec2 &vec);
        b2Vec2 vector(const sf::Vector2f &vec);

        /**
         * Computes the magnitude of a vector.
         */
        float magnitude(b2Vec2 vector);

        /**
         * Changes the magnitude of a vector.
         */
        b2Vec2 setMagnitude(b2Vec2 vector, float magnitude);

        /**
         * Finds the angle of a vector's direction.
         */
        float getAngle(b2Vec2 vector);

        /**
         * Computes a vector given an angle and magnitude.
         */
        b2Vec2 createVector(float angle, float magnitude);

        /**
         * Calculates the cross product of two vectors.
         */
        float cross(b2Vec2& left, b2Vec2& right);

        /**
         * Calculates the normal of a vector.
         */
        b2Vec2 normal(b2Vec2& a, b2Vec2& b, bool topRight);
    }
}

#endif
