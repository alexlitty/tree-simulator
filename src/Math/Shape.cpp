#include <tree/Math/Shape.hpp>

// Finds the center point of a rectangle.
sf::Vector2f tree::getCenter(sf::FloatRect rect)
{
    return sf::Vector2f(
        (rect.width - rect.left) / 2,
        (rect.height - rect.top) / 2
    );
}

// Finds the center point of a vertex array.
sf::Vector2f tree::getCenter(sf::VertexArray array)
{
    sf::Vector2f result;

    for (unsigned int i = 0; i < array.getVertexCount(); i++) {
        result.x += array[i].position.x;
        result.y += array[i].position.y;
    }

    result.x /= array.getVertexCount();
    result.y /= array.getVertexCount();
    return result;
}
