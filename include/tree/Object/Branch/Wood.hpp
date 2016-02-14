#ifndef TREESIMULATOR_OBJECT_BRANCH_WOOD_HPP
#define TREESIMULATOR_OBJECT_BRANCH_WOOD_HPP

#include <tree/Object/Branch/Branch.hpp>

namespace tree
{
    namespace branch
    {
        class Wood : public Branch
        {
            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        };
    }
}

#endif
