#include <tree/Object/Particles/PlanetCrumbs.hpp>

// Constructor.
tree::PlanetCrumbs::PlanetCrumbs()
: tree::Particles::Particles(500, 1000)
{
    m_fixtureTemplate.filter.maskBits = 0;
}

// Animates the crumbs.
void tree::PlanetCrumbs::animate(tree::Vector target)
{
    for (auto crumb : this->m_particles) {
        if (tree::similar(crumb->getPosition(), target, 1.0f)) {
            crumb->setLinearVelocity(tree::Vector(0, 0));
        }
    }
}
