#include <tree/Object/Branch.hpp>

// Activate the special abilities of this branch.
void tree::Branch::activate(bool activated)
{
    m_activated = activated;
}

// Show the preview of this branch.
void tree::Branch::preview(tree::Physical *parent, b2Vec2 anchor, b2Vec2 position)
{
    m_parent = parent;
    this->onPreview(anchor, position);
}

// Hide the preview of this branch.
void tree::Branch::hidePreview()
{
    m_parent = nullptr;
}

// Whether this branch is being previewed.
bool tree::Branch::isPreviewing() const
{
    return (m_parent != nullptr);
}

// Whether this branch has been permanently placed.
bool tree::Branch::isPlaced() const
{
    return m_placed;
}
