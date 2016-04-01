#ifndef TREESIMULATOR_OBJECT_TREE_LEAF
#define TREESIMULATOR_OBJECT_TREE_LEAF

#include <tree/Component.hpp>
#include <tree/Math.hpp>

namespace tree
{
    class Leaf : public Drawable
    {
        // Shape of the leaf.
        sf::CircleShape shape;

    public:

        // Position of the leaf.
        Point position;

        // Angle of the leaf.
        Angle angle;

        /**
         * Constructor.
         */
        Leaf();

        /**
         * Shoots seeds.
         */
        void shoot(tree::Stage &stage, Angle angle, Point currentVelocity);

        /**
         * Draws the leaf.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    };
}

#endif
