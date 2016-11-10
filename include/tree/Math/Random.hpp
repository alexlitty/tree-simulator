#ifndef TREESIMULATOR_MATH_RANDOM_HPP
#define TREESIMULATOR_MATH_RANDOM_HPP

#include <SFML/Graphics.hpp>
#include <tree/Math.hpp>

namespace tree
{
    /**
     * Seeds the random number generator.
     */
    void seedRandom(unsigned int number);

    /**
     * Generates a random float.
     */
    float random(float min, float max);

    /**
     * Generates a random integer.
     */
    int random(int min, int max);

    /**
     * Generates a random position, given a rendering size. 
     */
    sf::Vector2f random(float offset, sf::Vector2u right);

    /**
     * Generates a random angle.
     */
    Angle randomAngle();

    /**
     * Generates a random point on a circle.
     */
    Vector randomPointOnCircle(float radius, tree::Vector origin = tree::VectorZero);
    Vector randomPointOnCircle(sf::CircleShape &circle);

    /**
     * Generates a random point on a circle's border.
     */
    Vector randomPointOnBorder(sf::CircleShape shape);

    /**
     * Generates a float that varies from another float.
     */
    float vary(float x, float amount);
}

#endif
