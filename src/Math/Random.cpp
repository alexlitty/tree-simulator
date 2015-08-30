#include <cstdlib>
#include <tree/Math/Random.hpp>

// Seed the random number generator.
void tree::seedRandom(unsigned int number)
{
    std::srand(number);
}

// Generate a random float.
float tree::random(float min, float max)
{
    return min + (std::rand() / (RAND_MAX / (max - min)));
}

// Generate a random integer.
int tree::random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

// Generate a random position, given a rendering size.
sf::Vector2f tree::random(float offset, sf::Vector2u size)
{
    return sf::Vector2f(
        tree::random(
            offset,
            static_cast<float>(size.x)
        ),

        tree::random(
            offset,
            static_cast<float>(size.y)
        )
    );
}
