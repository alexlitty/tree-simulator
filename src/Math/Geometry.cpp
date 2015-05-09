#include <tree/Math/Geometry.hpp>

// Finds the distance between two vectors.
float tree::Math::distance(sf::Vector2f left, sf::Vector2f right)
{
    return std::sqrt(std::pow(right.x - left.x, 2) + std::pow(right.y - left.y, 2));
}

// Finds the center point of a rectangle.
sf::Vector2f tree::Math::getCenter(sf::FloatRect rect)
{
    return sf::Vector2f(
        (rect.width - rect.left) / 2,
        (rect.height - rect.top) / 2
    );
}

// Centers the origin of a shape.
void tree::Math::centerOrigin(sf::Shape& object)
{
    object.setOrigin(getCenter(object.getLocalBounds()));
}
