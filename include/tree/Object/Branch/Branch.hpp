#ifndef TREESIMULATOR_OBJECT_BRANCH_BRANCH_HPP
#define TREESIMULATOR_OBJECT_BRANCH_BRANCH_HPP

#include <tree/Component/Actor.hpp>
#include <tree/Component/Drawable.hpp>
#include <tree/Component/Physical.hpp>
#include <tree/Physics/Cardinal.hpp>

namespace tree
{
    /**
     * Enumeration of deviation directions.
     */
    enum class BranchDirection
    {
        Left,
        Middle,
        Right
    };

    /**
     * Base object for all tree branches.
     */
    class Branch : virtual public Actor, virtual public Drawable
    {
        // The current direction to use active abilities.
        tree::Cardinal abilityDirection;

    public:
    
        // Parent branch.
        Branch *parent;

        // Children branches.
        std::map<BranchDirection, Branch*> children;

        /**
         * Constructor.
         */
        Branch();

        /**
         * Destructor.
         */
        ~Branch();

        /**
         * Adds a child branch.
         */
        bool addChild(BranchDirection direction, Branch *child);

        /**
         * Removes a child branch.
         */
        void removeChild(BranchDirection direction);
        void removeChild(Branch *branch);

        
        /**
         * Toggle the direction this branch is using its active abilities.
         *
         * If direction is "none", then its active abilities are disabled.
         */
        void setAbilityDirection(tree::Cardinal direction);
    };
}

#endif
