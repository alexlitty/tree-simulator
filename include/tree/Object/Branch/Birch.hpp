#ifndef TREESIMULATOR_OBJECT_BRANCH_BIRCH_HPP
#define TREESIMULATOR_OBJECT_BRANCH_BIRCH_HPP

#include <tree/Object/Branch.hpp>
#include <tree/Object/Bullet.hpp>

namespace tree
{
    namespace branches
    {
        /**
         * Birch leaves, fired by birch branches.
         */
        class BirchLeaf : public Bullet
        {


        public:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        };

        /**
         * Birch branch.
         */
        class Birch : public Branch
        {
            std::vector<BirchLeaf> m_leaves;

            sf::CircleShape m_tempShape;
            sf::VertexArray m_branchShape;

        public:
            /**
             * Constructor.
             */
            Birch(b2Body *parent, b2Vec2 position, b2Vec2 anchor);

            /**
             * Upkeep leaves.
             */
            void act(std::vector<tree::object> &objects) override;

            /**
             * Draw branch and leaves.
             */
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        };
    }
}

#endif
