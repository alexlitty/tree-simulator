#ifndef TREESIMULATOR_MATH_RANDOM_HPP
#define TREESIMULATOR_MATH_RANDOM_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    /**
     * Seed the random number generator.
     */
    void seedRandom(unsigned int number);

    /**
     * Generate a random float.
     */
    float random(float min, float max);

    /**
     * Generate a random integer.
     */
    int random(int min, int max);

    /**
     * Generate a random position, given a rendering size. 
     */
    sf::Vector2f random(float offset, sf::Vector2u right);
}

#endif
