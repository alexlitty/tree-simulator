#ifndef TREESIMULATOR_OBJECT_BRANCH_BIRCH_HPP
#define TREESIMULATOR_OBJECT_BRANCH_BIRCH_HPP

#include <tree/Object/Branch.hpp>
#include <tree/Object/Bullet.hpp>

namespace tree
{
    namespace branches
    {
        /**
         * Birch leaf, fired by birch branches.
         */
        class BirchLeaf : public Bullet
        {
            // Triangle shape.
            sf::VertexArray m_triangle;
            sf::Vector2f m_center;

        public:
            /**
             * Constructor.
             */
            BirchLeaf(b2Vec2 position, float angle, b2Vec2 velocity);

            // Draw leaf.
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        };

        /**
         * Birch branch.
         */
        class Birch : public Branch
        {
            // Parent body.
            Physical *m_parent;

            // Initial position.
            b2Vec2 m_position;

            // Anchor point.
            b2Vec2 m_anchor;

            // Drawn shapes.
            sf::CircleShape m_tempShape;
            sf::VertexArray m_branchShape;

            // Shooting clock.
            sf::Clock m_clock;

        public:
            /**
             * Constructor.
             */
            Birch(Physical *parent, b2Vec2 position, b2Vec2 anchor);

            /**
             * Shoot leaves.
             */
            bool act(tree::Objects &objects) override;

            /**
             * Draw branch and leaves.
             */
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        };
    }
}

#endif
