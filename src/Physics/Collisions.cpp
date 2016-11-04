#include <tree/Physics/Collisions.hpp>

// Listen for collisions.
void tree::ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    Physical *a, *b;

    a = reinterpret_cast<Physical*>(
        contact->GetFixtureA()->GetBody()->GetUserData()
    );

    b = reinterpret_cast<Physical*>(
        contact->GetFixtureB()->GetBody()->GetUserData()
    );

    m_collisions.push_back(
        std::pair<Physical*, Physical*>(a, b)
    );
}

// Clear collisions.
void tree::ContactListener::clear()
{
    m_collisions.clear();
}

// Resolve the non-physical effects of collisions.
void tree::ContactListener::resolve()
{
    std::pair<Physical*, Physical*> objects;

    while (!m_collisions.empty()) {
        objects = m_collisions.front();
        m_collisions.pop_front();

        objects.first->onCollision(objects.second);
        objects.second->onCollision(objects.first);
    }
}

// Global instance of contact listener.
tree::ContactListener tree::collisions;
