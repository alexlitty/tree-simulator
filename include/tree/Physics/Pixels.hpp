#ifndef TREESIMULATOR_PHYSICS_PIXELS_HPP
#define TREESIMULATOR_PHYSICS_PIXELS_HPP

#include <cstdint>
#include <SFML/Graphics.hpp>

namespace tree
{
    // Amount of drawn pixels to represent a physical meter.
    extern const uint8_t PIXELS_PER_METER;

    // Convert physical distance to pixel distance.
    float pixels(float physical);

    // Convert physical vector to pixel vector.
    sf::Vector2f pixels(b2Vec2 vector);
}

#endif
