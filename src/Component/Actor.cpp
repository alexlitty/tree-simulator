#include <tree/Component.hpp>

// Constructor.
tree::Actor::Actor()
{
    m_isActor = true;
}

// Performs actions.
bool tree::Actor::act(tree::Stage &stage)
{
    return true;
}
