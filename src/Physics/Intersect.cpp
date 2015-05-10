#include <tree/Math/Vector.hpp>
#include <tree/Physics/Intersect.hpp>

// Finds the point where two lines intersect, if it exists.
bool tree::Intersect::lines(sf::Vector2f& A, sf::Vector2f& B, sf::Vector2f& C, sf::Vector2f& D, sf::Vector2f& result)
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

/*
// Determines if a box contains a point.
bool tree::intersect(tree::Bounding::Box& box, sf::Vector2f& point)
{
    return (box.a.y > point.y
         && box.a.x < point.x
         && (box.d.x) > point.x
         && (box.d.y) < point.y);
}

// Finds the point where a line intersects a box, if it exists.
bool tree::intersect(tree::Bounding::Box& box, sf::Vector2f& A, sf::Vector2f& B, sf::Vector2f& result)
{
    // Starting point is inside box.
    if (tree::intersect(box, A)) {
        result = A;
        return true;
    }

    // Intersects top line.
    if (tree::intersect(box.a, box.b, A, B, result)) {
        return true;
    }

    // Intersects left line.
    if (tree::intersect(box.a, box.c, A, B, result)) {
        return true;
    }

    // Intersects bottom line.
    if (tree::intersect(box.c, box.d, A, B, result)) {
        return true;
    }

    // Intersects right line, or no intersection occurs.
    return tree::intersect(box.d, box.b, A, B, result);
}

// Determines if two boxes overlap.
bool tree::intersect(sf::FloatRect A, sf::FloatRect B)
{
    return (A.left < (B.left + B.width)
         && (A.left + A.width) > B.left
         && A.top < (B.top + B.height)
         && (A.top + A.height) > B.top);
}*/
