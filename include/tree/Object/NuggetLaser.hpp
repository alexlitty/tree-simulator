#ifndef TREESIMULATOR_OBJECT_NUGGETLASER_HPP
#define TREESIMULATOR_OBJECT_NUGGETLASER_HPP

#include <tree/Component.hpp>

namespace tree
{
    class NuggetLaser
    : public Actor,
      public Drawable
    {
        // Parent object controlling the laser.
        tree::Physical *m_parent;

        // Visual nozzle.
        sf::CircleShape m_nozzle;

        // Cooldown timer.
        sf::Clock m_cooldown;

    public:

        /**
         * Constructor.
         */
        NuggetLaser(tree::Physical *parent);

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
