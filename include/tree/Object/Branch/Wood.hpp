#ifndef TREESIMULATOR_OBJECT_BRANCH_WOOD_HPP
#define TREESIMULATOR_OBJECT_BRANCH_WOOD_HPP

#include <tree/Object/Branch/Branch.hpp>

namespace tree
{
    namespace branch
    {
        class Wood : public Branch
        {
            sf::ConvexShape shape;

        public:
            /**
             * Constructor.
             */
            Wood();

            /**
             * Set anchor.
             */
            virtual void setAnchor(sf::Vector2f &a, sf::Vector2f &b);

            /**
             * Draw this branch.
             */ 
            virtual void drawSelf(sf::RenderTarget &target, sf::RenderStates states) const;
        };
    }
}

#endif
