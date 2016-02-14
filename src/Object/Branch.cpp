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
