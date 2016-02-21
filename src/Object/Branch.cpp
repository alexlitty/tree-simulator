#include <tree/Object/Branch.hpp>

// Constructor.
tree::Branch::Branch()
: abilityDirection(tree::Cardinal::None),
  parent(nullptr)
{

}

// Destructor.
tree::Branch::~Branch()
{
    for (auto &kv : children) {
        delete kv.second;
    }
}

// Gets the next anchor position for a new branch.
void tree::Branch::getNextAnchor(BranchDirection direction, sf::Vector2f &a, sf::Vector2f &b) const
{
    sf::Vector2f zero;
    a = zero;
    b = zero;
}

// Sets the anchor position this branch should attach to.
void tree::Branch::setAnchor(sf::Vector2f &a, sf::Vector2f &b)
{

}

// Adds a child branch.
bool tree::Branch::addChild(tree::BranchDirection direction, tree::Branch *child)
{
    if (child == nullptr) {
        return false;
    }

    // Ensure branch direction is free.
    auto search = children.find(direction);
    if (search != children.end()) {
        return false;
    }

    // Add child to branch.
    children[direction] = child;
    child->parent = this;

    // Set branching anchor.
    sf::Vector2f a, b;
    this->getNextAnchor(direction, a, b);
    child->setAnchor(a, b);
    return true;
}

// Removes a child branch, by direction.
void tree::Branch::removeChild(tree::BranchDirection direction)
{
    auto search = children.find(direction);
    if (search != children.end()) {
        delete search->second;
        children.erase(search);
    }
}

// Removes a child branch, by pointer.
void tree::Branch::removeChild(tree::Branch *branch)
{
    for (auto &child : children) {
        if (child.second == branch) {
            children.erase(child.first);
        }
    }
}

// Toggle the direction this branch is using its active abilities.
void tree::Branch::setAbilityDirection(tree::Cardinal direction)
{
    abilityDirection = direction;

    // Pass direction to children.
    for (auto &kv : children) {
        kv.second->setAbilityDirection(direction);
    }
}

// Draw this branch and children branches.
void tree::Branch::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto child : children) {
        child.second->draw(target, states);
    }

    this->drawSelf(target, states);
}

// Draw this branch. Should be overriden by child class.
void tree::Branch::drawSelf(sf::RenderTarget &target, sf::RenderStates states) const
{

}
