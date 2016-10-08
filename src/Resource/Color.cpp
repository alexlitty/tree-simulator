#include <tree/Math/Random.hpp>
#include <tree/Resource/Color.hpp>

// Generate a color, based on a predefined palette.
sf::Color tree::paletteColor(tree::palette palette)
{
    unsigned char r, g, b;

    switch (palette)
    {
        case tree::palette::white:
            r = g = b = tree::random(235, 245);

        case tree::palette::water:
            r = g = tree::random(0, 50);
            b = tree::random(200, 225);

        case tree::palette::rock:
            r = g = b = tree::random(100, 175);
            break;

        case tree::palette::fire:
            r = tree::random(255, 255);
            g = tree::random(0, 100);
            b = 0;
            break;

        case tree::palette::lava:
            if (tree::random(0, 3) == 0) {
                r = g = b = tree::random(10, 35);
            } else {
                r = tree::random(200, 225);
                g = tree::random(0, 100);
                b = 0;
            }
            break;

        case tree::palette::light:
            r = g = tree::random(225, 255);
            b = tree::random(150, 200);
            break;

        default:
            r = tree::random(0, 255);
            g = tree::random(0, 255);
            b = tree::random(0, 255);
            break;
    }

    return sf::Color(r, g, b);
}
