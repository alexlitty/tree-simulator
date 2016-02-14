#ifndef TREESIMULATOR_BRANCH_JAPANESECHERRY
#define TREESIMULATOR_BRANCH_JAPANESECHERRY

#include <tree/Object/Branch/Branch.hpp>

namespace tree
{
    namespace branch
    {
        class JapaneseCherry : public Branch
        {
        public:

            /**
             * Constructor.
             */
            JapaneseCherry();

            /**
             * Draw the branch.
             */
            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        };
    }
}

#endif
