#ifndef TREESIMULATOR_MATH_VECTOR_HPP
#define TREESIMULATOR_MATH_VECTOR_HPP

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include <tree/Math/Angle.hpp>

namespace tree
{
    struct Vector
    {
        float x;
        float y;

        /**
         * Default constructor.
         */
        Vector();

        /**
         * Constructors.
         */
        Vector(float _x, float _y);
        Vector(Angle angle, float magnitude);

        /**
         * Conversion constructors.
         */
        Vector(const sf::Vector2f &other);
        Vector(const b2Vec2 &other);

        /**
         * Calculates the angle made by this vector alone.
         */
        Angle getAngle() const;

        /**
         * Calculates the angle made by this vector and another vector.
         */
        Angle getAngle(Vector &other) const;

        /**
         * Calculates and sets the magnitude of this vector.
         */
        float getMagnitude() const;
        void setMagnitude(float magnitude);

        /**
         * Extends this vector at an angle.
         */
        void extend(Angle angle, float magnitude);

        /**
         * Finds the distance between this and another vector.
         */
        float distance(Vector other) const;

        /**
         * Calculates percentage of progress made toward a final vector.
         */
        float progress(Vector &start, Vector &end) const;

        /**
         * Whether this vector is near another vector.
         */
        bool isNear(Vector other, float threshold = 10.0f) const;

        /**
         * Finds the center between this and another vector.
         */
        Vector center(Vector other) const;

        /**
         * Eases toward another vector.
         *
         * Returns false if this vector is now the other vector, true otherwise.
         */
        bool easeToward(Vector &other, Vector increment);

        /**
         * Returns a copy of this vector rotated about another vector.
         */
        Vector rotated(Angle angle, Vector other = Vector(0.0f, 0.0f));

        /**
         * Calculates vector normals, alone or with another vector.
         */
        Vector normal() const;
        Vector normal(tree::Vector& other) const;

        /**
         * Calculates the dot product of this and another vector.
         */
        float dot(Vector& other) const;

        /**
         * Calculates the cross product of this and another vector.
         */
        float cross(Vector& other) const;

        /**
         * Convert to SFML vector.
         */
        sf::Vector2f toDrawable() const;
        operator sf::Vector2f() const;

        /**
         * Convert to SFML vertex.
         */
        operator sf::Vertex() const;

        /**
         * Convert to Box2D vector.
         */
        b2Vec2 toPhysical() const;
        operator b2Vec2() const;

        /**
         * Mathematical operators.
         */
        Vector& operator -=(const Vector &rhs);
        Vector& operator +=(const Vector &rhs);
        Vector& operator *=(const int rhs);
        Vector& operator *=(const float rhs);
        Vector& operator /=(const int rhs);
        Vector& operator /=(const float rhs);
    };

    /**
     * Mathematical operators.
     */
    Vector operator -(Vector lhs, const Vector &rhs);
    Vector operator +(Vector lhs, const Vector &rhs);
    Vector operator *(Vector lhs, const int rhs);
    Vector operator *(Vector lhs, const float rhs);
    Vector operator /(Vector lhs, const int rhs);
    Vector operator /(Vector lhs, const float rhs);

    /**
     * Logical operators.
     */
    bool operator ==(const Vector& lhs, const Vector &rhs);
    bool operator !=(const Vector& lhs, const Vector &rhs);
    bool similar(const Vector& lhs, const Vector& rhs, float epsilon = 0.001f);

    /**
     * Common vectors.
     */
    extern const Vector VectorZero;
}

#endif
