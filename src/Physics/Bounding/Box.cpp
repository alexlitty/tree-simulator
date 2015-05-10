#include <tree/Physics/Bounding/Box.hpp>

// Default constructor.
tree::Bounding::Box::Box()
{

}

// Constructor, from SFML rectangle.
tree::Bounding::Box::Box(sf::FloatRect rect)
: aOriginal(rect.left, rect.top),
  bOriginal(rect.left + rect.width, rect.top),
  cOriginal(rect.left, rect.top + rect.height),
  dOriginal(rect.left + rect.width, rect.top + rect.height),
  a(aOriginal),
  b(bOriginal),
  c(cOriginal),
  d(dOriginal)
{

}

// Constructor, from individual points.
tree::Bounding::Box::Box(sf::Vector2f& aInit, sf::Vector2f& bInit, sf::Vector2f& cInit, sf::Vector2f& dInit)
: aOriginal(aInit),
  bOriginal(bInit),
  cOriginal(cInit),
  dOriginal(dInit),
  a(aInit),
  b(bInit),
  c(cInit),
  d(dInit)
{
    
}

// Returns the size of this box.
sf::Vector2f tree::Bounding::Box::getSize() const
{
    return sf::Vector2f(bOriginal.x - aOriginal.x, dOriginal.y - bOriginal.y);
}

// Access the current points by index number.
sf::Vector2f& tree::Bounding::Box::operator[](unsigned int index)
{
    if (index == 0) {
        return a;
    } else if (index == 1) {
        return b;
    } else if (index == 2) {
        return c;
    } else {
        return d;
    }
}
