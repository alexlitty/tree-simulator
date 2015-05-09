#include <math/vector.hpp>
#include <physics/intersect.hpp>

// Finds the point where two lines intersect, if it exists.
bool tree::Intersect(sf::Vector2f& A, sf::Vector2f& B, sf::Vector2f& C, sf::Vector2f& D, sf::Vector2f& result)
{
    sf::Vector2f R = (B - A);
    sf::Vector2f S = (D - C);
    sf::Vector2f CmA = (C - A);

    float rs = tree::math::cross(R, S);
    float tNum = tree::math::cross(CmA, S);

    float t = tNum / rs;
    float u = tree::math::cross(CmA, R) / rs;

    // Lines are parallel or collinear. Consider collinear a non-collision.
    if (rs == 0) {
        return false; 
    }

    // Lines interesect.
    if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
        result = A + (t * R);
        return true;
    }

    // Lines do not intersect.
    return false;
}

// Determines if a box contains a point.
bool tree::Intersect(sf::FloatRect& box, sf::Vector2f& point)
{
    return (box.top > point.y
         && box.left < point.x
         && (box.left + box.width) > point.x
         && (box.top + box.height) < point.y);
}

// Finds the point where a line intersects a box, if it exists.
bool tree::Intersect(sf::FloatRect& box, sf::Vector2f& A, sf::Vector2f& B, sf::Vector2f& result)
{
    // Starting point is inside box.
    if (tree::Intersect(box, A)) {
        result = A;
        return true;
    }

    // Intersects top line.
    float right = box.left + box.width;
    sf::Vector2f topLeft(box.left, box.top);
    sf::Vector2f topRight(right, box.top);
    if (tree::Intersect(topLeft, topRight, A, B, result)) {
        return true;
    }

    // Intersects left line.
    float bottom = box.top + box.height;
    sf::Vector2f bottomLeft(box.left, bottom);
    if (tree::Intersect(topLeft, bottomLeft, A, B, result)) {
        return true;
    }

    // Intersects bottom line.
    sf::Vector2f bottomRight(right, bottom);
    if (tree::Intersect(bottomLeft, bottomRight, A, B, result)) {
        return true;
    }

    // Intersects right line, or no intersection occurs.
    return tree::Intersect(topRight, bottomRight, A, B, result);
}

// Determines if two boxes overlap.
bool tree::Intersect(sf::FloatRect A, sf::FloatRect B)
{
    return (A.left < (B.left + B.width)
         && (A.left + A.width) > B.left
         && A.top < (B.top + B.height)
         && (A.top + A.height) > B.top);
}
