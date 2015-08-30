#include <tree/Math.hpp>
#include <tree/Utility/Brush.hpp>

tree::palette tree::brush::palette = tree::palette::random;

void tree::brush::spots(sf::RenderTarget *target, unsigned int count, float minRadius, float maxRadius)
{
    sf::CircleShape circle;
    circle.setPointCount(60);

    sf::Vector2u size = target->getSize();
    for (unsigned int i = 0; i < count; i++) {
        circle.setRadius(
            tree::random(minRadius, maxRadius)
        );
        circle.setPosition(
            tree::random(-maxRadius, size)
        );
        circle.setFillColor(
            tree::paletteColor(tree::brush::palette)
        );
        target->draw(circle);
    }
}
