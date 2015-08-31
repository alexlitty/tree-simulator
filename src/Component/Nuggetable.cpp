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
