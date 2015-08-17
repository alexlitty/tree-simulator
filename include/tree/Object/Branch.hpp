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
    class Branch : virtual public Actor, virtual public Drawable
    {
    protected:
        // Whether the special abilities of this branch are activated.
        bool m_activated;

    public:

        std::vector<b2Fixture*> fixtures;

        /**
         * Activate the special abilities of this branch.
         */
        void activate(bool activated = true);
    };
}

#endif
