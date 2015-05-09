#include <physics/boundary.hpp>

// Default boundary constructor.
tree::Boundary::Boundary()
{
    info = nullptr;
}

// Line boundary constructor.
tree::Boundary::Boundary(tree::Line line)
: tree::Boundary::Boundary()
{
    Set(line);
}

// Box boundary constructor.
tree::Boundary::Boundary(sf::FloatRect box)
: tree::Boundary::Boundary()
{
    Set(box);
}

// Copy constructor.
tree::Boundary::Boundary(tree::Boundary& other)
: tree::Boundary::Boundary()
{
    // Copying a line boundary.
    if (other.type == tree::Boundary::TYPE::LINE) {
         Set(*reinterpret_cast<tree::Line*>(other.info));
    }

    // Copying a box boundary.
    else if (other.type == tree::Boundary::TYPE::BOX) {
        Set(*reinterpret_cast<sf::FloatRect*>(other.info));
    }
}

// Move constructor.
tree::Boundary::Boundary(tree::Boundary&& other)
: tree::Boundary::Boundary()
{
    Swap(other);
}

// Destructor.
tree::Boundary::~Boundary()
{
    DeleteInfo();
}

// Swaps this boundary with another boundary.
void tree::Boundary::Swap(tree::Boundary& other)
{
    std::swap(type, other.type);
    std::swap(info, other.info);
}

// Deletes the information about this boundary.
void tree::Boundary::DeleteInfo()
{
    if (type == tree::Boundary::TYPE::LINE) {
        delete reinterpret_cast<tree::Line*>(info);
    } else if (type == tree::Boundary::TYPE::BOX) {
        delete reinterpret_cast<sf::FloatRect*>(info);
    }
}

// Assigns new line parameters to this boundary.
void tree::Boundary::Set(tree::Line line)
{
    DeleteInfo();
    type = tree::Boundary::TYPE::LINE;
    info = new tree::Line(line);
}

// Assigns new box parameters to this boundary.
void tree::Boundary::Set(sf::FloatRect box)
{
    DeleteInfo();
    type = tree::Boundary::TYPE::BOX;
    info = new sf::FloatRect(box);
}

// Checks if this boundary collides with another boundary.
bool tree::Boundary::Collides(tree::Boundary& other, sf::Vector2f& result)
{
    return true;
}

// Assignment operator.
tree::Boundary& tree::Boundary::operator=(tree::Boundary other)
{
    Swap(other);
    return *this;
}
