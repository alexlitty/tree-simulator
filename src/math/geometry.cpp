#include <math/geometry.hpp>

// Finds the distance between two vectors.
float tree::math::distance(sf::Vector2f left, sf::Vector2f right)
{
    return std::sqrt(std::pow(right.x - left.x, 2) + std::pow(right.y - left.y, 2));
}

// Finds the center point of a rectangle.
sf::Vector2f tree::math::get_center(sf::FloatRect rect)
{
    return sf::Vector2f(
        (rect.width - rect.left) / 2,
        (rect.height - rect.top) / 2
    );
}

// Centers the origin of a shape.
void tree::math::center_origin(sf::Shape& object)
{
    object.setOrigin(get_center(object.getLocalBounds()));
}
