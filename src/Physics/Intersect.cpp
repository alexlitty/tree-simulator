#include <tree/Math/Vector.hpp>
#include <tree/Physics/Intersect.hpp>

// Finds the point where two lines intersect, if it exists.
bool tree::intersect(sf::Vector2f& A, sf::Vector2f& B, sf::Vector2f& C, sf::Vector2f& D, sf::Vector2f& result)
{
    sf::Vector2f R = (B - A);
    sf::Vector2f S = (D - C);
    sf::Vector2f CmA = (C - A);

    float rs = tree::Math::cross(R, S);
    float tNum = tree::Math::cross(CmA, S);

    float t = tNum / rs;
    float u = tree::Math::cross(CmA, R) / rs;

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
bool tree::intersect(sf::FloatRect& box, sf::Vector2f& point)
{
    return (box.top > point.y
         && box.left < point.x
         && (box.left + box.width) > point.x
         && (box.top + box.height) < point.y);
}

// Finds the point where a line intersects a box, if it exists.
bool tree::intersect(sf::FloatRect& box, sf::Vector2f& A, sf::Vector2f& B, sf::Vector2f& result)
{
    // Starting point is inside box.
    if (tree::intersect(box, A)) {
        result = A;
        return true;
    }

    // intersects top line.
    float right = box.left + box.width;
    sf::Vector2f topLeft(box.left, box.top);
    sf::Vector2f topRight(right, box.top);
    if (tree::intersect(topLeft, topRight, A, B, result)) {
        return true;
    }

    // intersects left line.
    float bottom = box.top + box.height;
    sf::Vector2f bottomLeft(box.left, bottom);
    if (tree::intersect(topLeft, bottomLeft, A, B, result)) {
        return true;
    }

    // intersects bottom line.
    sf::Vector2f bottomRight(right, bottom);
    if (tree::intersect(bottomLeft, bottomRight, A, B, result)) {
        return true;
    }

    // intersects right line, or no intersection occurs.
    return tree::intersect(topRight, bottomRight, A, B, result);
}

// Determines if two boxes overlap.
bool tree::intersect(sf::FloatRect A, sf::FloatRect B)
{
    return (A.left < (B.left + B.width)
         && (A.left + A.width) > B.left
         && A.top < (B.top + B.height)
         && (A.top + A.height) > B.top);
}
