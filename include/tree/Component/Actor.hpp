#ifndef TREESIMULATOR_COMPONENT_ACTOR_HPP
#define TREESIMULATOR_COMPONENT_ACTOR_HPP

#include <tree/Component/Object.hpp>

namespace tree
{
    /**
     * An object which performs actions.
     */
    class Actor : virtual public Object
    {
    public:
        /**
         * Constructor.
         */
        Actor();

        /**
         * Perform actions.
         *
         * Returns false if this object should be destroyed.
         */
        virtual bool act(tree::Objects &objects);
    };
}

#endif