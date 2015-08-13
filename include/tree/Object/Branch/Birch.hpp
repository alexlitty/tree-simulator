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
            void draw(sf::RenderTarget &target, sf::RenderStates states);
        };

        /**
         * Birch branch.
         */
        class Birch : public Branch
        {
            std::vector<BirchLeaf> m_leaves;

        public:
            /**
             * Upkeep leaves.
             */
            void act() override;

            /**
             * Draw branch and leaves.
             */
            void draw(sf::RenderTarget &target, sf::RenderStates states);
        };
    }
}

#endif
