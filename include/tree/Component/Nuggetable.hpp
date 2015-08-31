#ifndef TREESIMULATOR_COMPONENT_NUGGETABLE_HPP
#define TREESIMULATOR_COMPONENT_NUGGETABLE_HPP

#include <tree/Object/Nugget.hpp>

namespace tree
{
    /**
     * An object composed of nuggets.
     */
    class Nuggetable : virtual public Physical
    {
        bool m_isNuggetableTarget = false;

    public:

        // Nugget composition.
        tree::Nuggets nuggets;

        /**
         * Constructor.
         */
        Nuggetable();

        /**
         * Receives a new nugget.
         */
        virtual void receiveNugget(tree::nugget nugget);

        /**
         * Whether this object is highlighted by the nugget laser.
         */
        bool isNuggetableTarget() const;

        /**
         * Highlights this object for the nugget laser.
         */
        void markNuggetableTarget(bool mark = true);
    };
}

#endif
