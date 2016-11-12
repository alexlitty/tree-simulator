#include <tree/Component/Lifeform.hpp>

// Constructor.
tree::Lifeform::Lifeform(tree::Faction faction)
: m_faction(faction)
{
    m_isLifeform = true;
}

// Checks the opinion between two lifeforms.
tree::Opinion tree::Lifeform::getOpinion(tree::Lifeform &other) const
{
    // Be kind to your own.
    if (this->m_faction == other.m_faction) {
        return tree::Opinion::friendly;
    }

    // Be harsh to others.
    return tree::Opinion::hostile;
}

// Quickly checks friendliness.
bool tree::Lifeform::isFriendly(tree::Lifeform &other) const
{
    return (this->getOpinion(other) != tree::Opinion::hostile);
}

// Quickly checks hostility.
bool tree::Lifeform::isHostile(tree::Lifeform &other) const
{
    return !this->isFriendly(other);
}

// Act.
void tree::Lifeform::act()
{

}
