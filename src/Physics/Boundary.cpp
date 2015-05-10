#include <tree/Math/Geometry.hpp>
#include <tree/Physics/Boundary.hpp>
#include <tree/Physics/Intersect.hpp>

// Default boundary constructor.
tree::Boundary::Boundary()
: info(nullptr),
  transform(nullptr)
{

}

// Line boundary constructor.
tree::Boundary::Boundary(tree::Line line)
: tree::Boundary::Boundary()
{
    set(line);
}

// Box boundary constructor.
tree::Boundary::Boundary(tree::Bounding::Box& box)
: tree::Boundary::Boundary()
{
    set(box);
}

// Copy constructor.
tree::Boundary::Boundary(tree::Boundary& other)
: tree::Boundary::Boundary()
{
    // Copying a line boundary.
    if (other.type == tree::Boundary::TYPE::LINE) {
         set(*reinterpret_cast<tree::Line*>(other.info));
    }

    // Copying a box boundary.
    else if (other.type == tree::Boundary::TYPE::BOX) {
        set(*reinterpret_cast<tree::Bounding::Box*>(other.info));
    }
}

// Move constructor.
tree::Boundary::Boundary(tree::Boundary&& other)
: tree::Boundary::Boundary()
{
    swap(other);
}

// Destructor.
tree::Boundary::~Boundary()
{
    deleteInfo();
}

// Swaps this boundary with another boundary.
void tree::Boundary::swap(tree::Boundary& other)
{
    std::swap(type, other.type);
    std::swap(info, other.info);
}

// Deletes the information about this boundary.
void tree::Boundary::deleteInfo()
{
    if (type == tree::Boundary::TYPE::LINE) {
        delete reinterpret_cast<tree::Line*>(info);
    } else if (type == tree::Boundary::TYPE::BOX) {
        delete reinterpret_cast<tree::Bounding::Box*>(info);
    }
}

#include <iostream>
// Applies the current transformation to bounding information.
void tree::Boundary::update()
{
    if (info != nullptr) {
        tree::Bounding::Box *box = reinterpret_cast<tree::Bounding::Box*>(info);
        box->a = transform->transformPoint(box->aOriginal);
        box->b = transform->transformPoint(box->bOriginal);
        box->c = transform->transformPoint(box->cOriginal);
        box->d = transform->transformPoint(box->dOriginal);
    }
}

// Assigns new line parameters to this boundary.
void tree::Boundary::set(tree::Line line)
{
    deleteInfo();
    type = tree::Boundary::TYPE::LINE;
    info = new tree::Line(line);
}

// Assigns new box parameters to this boundary.
void tree::Boundary::set(tree::Bounding::Box& box)
{
    deleteInfo();
    type = tree::Boundary::TYPE::BOX;
    info = new tree::Bounding::Box(box);
    update();
}

// Blindly retrieves bounding box parameters.
tree::Bounding::Box* tree::Boundary::getBox()
{
    return reinterpret_cast<tree::Bounding::Box*>(info);
}

// Checks if this boundary contains a point.
bool tree::Boundary::contains(sf::Vector2f& point)
{
    tree::Bounding::Box *box = reinterpret_cast<tree::Bounding::Box*>(info);

    // Find longest side of box.
    float width = box->bOriginal.x - box->aOriginal.x;
    float height = box->dOriginal.y - box->bOriginal.y;

    // Extend point into a line. Find box lines that intersect it.
    sf::Vector2f result;
    sf::Vector2f end((width > height) ? width : height, point.y);
    char count = 0;
    tree::Intersect::lines(point, end, box->a, box->b, result) && count++;
    tree::Intersect::lines(point, end, box->a, box->c, result) && count++;
    tree::Intersect::lines(point, end, box->c, box->d, result) && count++;
    tree::Intersect::lines(point, end, box->d, box->a, result) && count++;
    return (count == 1);
}

// Checks if this boundary intersects a line.
bool tree::Boundary::collides(sf::Vector2f& start, sf::Vector2f& end, sf::Vector2f& result)
{
    tree::Bounding::Box *box = reinterpret_cast<tree::Bounding::Box*>(info);

    // Start point is inside bounds.
    if (contains(start)) {
        result = start;
        return true;
    }

    // Intersects top line.
    if (tree::Intersect::lines(box->a, box->b, start, end, result)) {
        return true;
    }

    // Intersects left line.
    if (tree::Intersect::lines(box->a, box->c, start, end, result)) {
        return true;
    }

    // Intersects bottom line.
    if (tree::Intersect::lines(box->c, box->d, start, end, result)) {
        return true;
    }

    // Intersects right line, or no intersection occurs.
    return tree::Intersect::lines(box->d, box->b, start, end, result);
}

// Checks if this boundary collides with another boundary.
bool tree::Boundary::collides(tree::Boundary& other, tree::Line& trajectory, sf::Vector2f& result)
{
    // Find nearest point to each boundary. 

    // Use trajectory.
    return false;
}

// Returns the nearest points of two boundaries.
void tree::Boundary::nearestPoints(tree::Boundary& other, sf::Vector2f& thisResult, sf::Vector2f& otherResult)
{
    tree::Bounding::Box *left = getBox(), *right = other.getBox();
    sf::Vector2f *leftPoint, *rightPoint;

    sf::Vector2f *nearestLeft, *nearestRight;
    float distance, nearestDistance = -1;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            leftPoint = &((*left)[i]);
            rightPoint = &((*right)[i]);

            distance = Math::distance(*leftPoint, *rightPoint);
            if (nearestDistance == -1 || distance < nearestDistance) {
                nearestDistance = distance;
                nearestLeft = leftPoint;
                nearestRight = rightPoint;
            }
        }
    }

    thisResult = *nearestLeft;
    otherResult = *nearestRight;
}

// Assignment operator.
tree::Boundary& tree::Boundary::operator=(tree::Boundary other)
{
    swap(other);
    return *this;
}

// Draw this boundary. @@@ Only supports boxes
void tree::Boundary::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Get box parameters.
    tree::Bounding::Box *box = reinterpret_cast<tree::Bounding::Box*>(info);
    sf::Vector2f size(box->getSize());

    // Decorate shape.
    sf::RectangleShape shape(size);
    shape.setFillColor(sf::Color::Magenta);
    Math::centerOrigin(shape);
    shape.setPosition(sf::Vector2f(0, 0));

    if (transform != nullptr) {
        states.transform *= (*transform);
    }

    target.draw(shape, states);
}
