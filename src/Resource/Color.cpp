#include <tree/Math/Random.hpp>
#include <tree/Resource/Color.hpp>

// Generate a color, based on a predefined palette.
sf::Color tree::paletteColor(tree::palette palette)
{
    unsigned char r, g, b;

    switch (palette)
    {
        case tree::palette::rock:
            r = g = b = tree::random(100, 175);
            break;

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

// Get the palette of a nugget.
tree::palette tree::nuggetPalette(tree::nugget nug)
{
    switch (nug)
    {
        case tree::nugget::rock:
            return palette::rock;

        case tree::nugget::lava:
            return palette::fire;

        default:
            return palette::random;
    }
}

// Generate a base nugget color.
sf::Color tree::nuggetColor(tree::nugget nug)
{
    return tree::paletteColor(tree::nuggetPalette(nug));
}
