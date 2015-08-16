#include <tree/Component/Actor.hpp>

// Constructor.
tree::Actor::Actor()
{
    m_isActor = true;
}

// Performs actions.
bool tree::Actor::act(tree::Objects &objects)
{
    return true;
}
