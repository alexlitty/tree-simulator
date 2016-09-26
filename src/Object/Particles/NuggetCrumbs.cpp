#include <tree/Object/Particles/NuggetCrumbs.hpp>

// Constructor.
tree::NuggetCrumbs::NuggetCrumbs()
: tree::Particles::Particles(500, 1000)
{
    m_fixtureTemplate.filter.maskBits = 0;
}

// Animates the crumbs.
void tree::NuggetCrumbs::animate(tree::Vector target)
{
    for (auto crumb : this->m_particles) {
        tree::Vector crumbPosition = crumb->getPosition();

        if (tree::similar(crumbPosition, target, 1.0f)) {
            crumb->setLinearVelocity(tree::Vector(0, 0));
            continue;
        }

        /*tree::Angle angle = crumbPosition.getAngle(target);
        tree::Vector velocity(angle, 5.0f);
        crumb->setLinearVelocity(velocity);*/
    }
}
