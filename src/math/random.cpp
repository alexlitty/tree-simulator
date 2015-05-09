#include <cstdlib>
#include <ctime>
#include <math/random.hpp>

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
