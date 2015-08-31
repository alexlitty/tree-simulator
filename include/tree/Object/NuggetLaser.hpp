#ifndef TREESIMULATOR_OBJECT_NUGGETLASER_HPP
#define TREESIMULATOR_OBJECT_NUGGETLASER_HPP

#include <tree/Component.hpp>

namespace tree
{
    class NuggetLaser
    : public Actor,
      public Drawable,
      public b2RayCastCallback
    {
        // Parent object controlling the laser.
        tree::Physical *m_parent;

        // Visual laser.
        sf::VertexArray m_laser;

        // Laser goal.
        b2Vec2 m_goal;

        // Laser target.
        tree::Nuggetable *m_target = nullptr;

        // Cooldown timer.
        sf::Clock m_cooldown;

        /**
         * Swaps the laser target with a new one.
         */
        void swapTarget(tree::Nuggetable *target);

    public:

        // Whether the laser is being used.
        bool active = false;

        /**
         * Constructor.
         */
        NuggetLaser(tree::Physical *parent);

        /**
         * Check the result of a physical ray cast.
         */
        float ReportFixture(b2Fixture *fixture, const b2Vec2 &position, const b2Vec2 &normal, float fraction) override;

        /**
         * Fires the laser.
         */
        void fire(tree::nugget nugget);

        /**
         * Act.
         */
        bool act(tree::Stage &stage) override;

        /**
         * Draw.
         */
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}

#endif
