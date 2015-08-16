#include <tree/Math.hpp>
#include <tree/Physics.hpp>

const uint8_t tree::PIXELS_PER_METER = 1;

// Convert physical distance to pixel distance.
float tree::pixels(float distance)
{
    return tree::PIXELS_PER_METER * distance;
}

// Convert physical vector to pixel vector.
sf::Vector2f tree::pixels(b2Vec2 vector)
{
    return tree::Math::vector(
        tree::PIXELS_PER_METER * vector
    );
}
