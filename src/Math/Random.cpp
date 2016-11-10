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

// Generates a random angle.
tree::Angle tree::randomAngle()
{
    Angle angle;
    angle.radians(tree::random(0.0f, TWO_PI));
    return angle;
}

// Generates a random point on a circle.
#include <iostream>
tree::Vector tree::randomPointOnCircle(float radius, tree::Vector origin)
{
    tree::Vector localPoint(
        tree::randomAngle(),
        tree::random(0.0f, radius)
    );

    return localPoint + origin;
}

tree::Vector tree::randomPointOnCircle(sf::CircleShape &circle)
{
    return tree::randomPointOnCircle(circle.getRadius(), circle.getPosition());
}

// Generates a random point on a circle's border.
tree::Vector tree::randomPointOnBorder(sf::CircleShape shape)
{
    Angle angle;
    angle.radians(tree::random(-PI, PI));

    float magnitude = shape.getRadius();

    return Vector(angle, magnitude);
}

// Generates a float that varies from another float.
float tree::vary(float x, float amount)
{
    return tree::random(x - amount, x + amount);
}
