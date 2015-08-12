#include <tree/Math/Random.hpp>
#include <tree/Resource/Color.hpp>

const unsigned char tree::palette::random = 0;
const unsigned char tree::palette::fire = 1;

sf::Color tree::paletteColor(const unsigned char palette = 0)
{
    unsigned char r, g, b;

    switch (palette)
    {
        case tree::palette::fire:
            r = tree::random(255, 255);
            g = tree::random(0, 100);
            b = 0;
            break;

        default:
            r = tree::random(0, 255);
            g = tree::random(0, 255);
            b = tree::random(0, 255);
            break;
    }

    return sf::Color(r, g, b);
}
