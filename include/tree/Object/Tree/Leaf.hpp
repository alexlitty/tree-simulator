#ifndef TREESIMULATOR_OBJECT_TREE_LEAF
#define TREESIMULATOR_OBJECT_TREE_LEAF

#include <tree/Component.hpp>
#include <tree/Math.hpp>
#include <tree/Object/Weapon/Seed.hpp>

namespace tree
{
    class Leaf : public Drawable
    {
        // Player this leaf is attached to.
        Physical* parent;

        // Shape of the leaf.
        sf::CircleShape shape;

    public:

        // Relative position of the leaf.
        Vector position;

        /**
         * Constructor.
         */
        Leaf(Physical* _parent);

        /**
         * Shoots seeds.
         */
        void shoot(std::vector<tree::weapon::Seed*> &seeds, Angle angle);

        /**
         * Draws the leaf.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    };
}

#endif
