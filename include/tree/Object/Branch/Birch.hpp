#ifndef TREESIMULATOR_OBJECT_BRANCH_BIRCH_HPP
#define TREESIMULATOR_OBJECT_BRANCH_BIRCH_HPP

#include <tree/Component.hpp>
#include <tree/Object/Branch.hpp>

namespace tree
{
    namespace branches
    {
        /**
         * Birch leaf, fired by birch branches.
         */
        class BirchLeaf
        : public Drawable,
          public Expirable,
          public Physical
        {
        protected:
            // Triangle shape.
            sf::VertexArray m_triangle;
            sf::Vector2f m_center;
            mutable bool m_frameDirection;
            mutable float m_frame;

        public:
            /**
             * Constructor.
             */
            BirchLeaf(b2Vec2 position, float angle, b2Vec2 velocity);

            /**
             * Draw leaf.
             */
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        };

        /**
         * Birch branch.
         */
        class Birch : public Branch
        {
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
            Birch();

            /**
             * Preview the placement of this branch.
             */
            void onPreview(b2Vec2 anchor, b2Vec2 position) override;

            /**
             * Place this branch permanently.
             */
            void place() override;

            /**
             * Shoot leaves.
             */
            bool act(tree::Stage &stage) override;

            /**
             * Draw branch and leaves.
             */
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        };
    }
}

#endif
