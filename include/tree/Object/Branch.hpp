#ifndef TREESIMULATOR_OBJECT_BRANCH_HPP
#define TREESIMULATOR_OBJECT_BRANCH_HPP

#include <tree/Component/Actor.hpp>
#include <tree/Component/Drawable.hpp>
#include <tree/Component/Physical.hpp>

namespace tree
{
    /**
     * Base object for all tree branches.
     */
    class Branch : public Actor, public Drawable, public Physical
    {
        // Whether the special abilities of this branch are activated.
        bool m_activated;

    public:
        /**
         * Activate the special abilities of this branch.
         */
        void activate(bool activated = true);
    };
}

#endif
