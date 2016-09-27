#include <tree/Component.hpp>

// Constructor.
tree::Nuggetable::Nuggetable()
{
    m_isNuggetable = true;
}

// Receives a new nugget.
void tree::Nuggetable::receiveNugget(tree::nugget nugget)
{

}

// Takes nuggets from another nuggetable object.
void tree::Nuggetable::takeNuggets(tree::Nuggetable *other)
{
    this->nuggets.add(other->nuggets);
    other->nuggets.clear();
}

// Whether this object is highlighted by the nugget laser.
bool tree::Nuggetable::isNuggetableTarget() const
{
    return m_isNuggetableTarget;
}

// Highlights this object for the nugget laser.
void tree::Nuggetable::markNuggetableTarget(bool mark)
{
    m_isNuggetableTarget = mark;
}
