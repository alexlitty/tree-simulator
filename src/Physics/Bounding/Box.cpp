#include <tree/Physics/Bounding/Box.hpp>

// Default constructor.
tree::Bounding::Box::Box()
{

}

// Constructor, from SFML rectangle.
tree::Bounding::Box::Box(sf::FloatRect& rect)
: a(rect.left, rect.top),
  b(rect.left + rect.width, rect.top),
  c(rect.left, rect.top + rect.height),
  d(rect.left + rect.width, rect.top + rect.height)
{

}

// Constructor, from individual points.
tree::Bounding::Box::Box(sf::Vector2f& aInit, sf::Vector2f& bInit, sf::Vector2f& cInit, sf::Vector2f& dInit)
: a(aInit),
  b(bInit),
  c(cInit),
  d(dInit)
{
    
}
