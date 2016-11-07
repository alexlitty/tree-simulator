#ifndef TREESIMULATOR_COMPONENT_EXPIRABLE_HPP
#define TREESIMULATOR_COMPONENT_EXPIRABLE_HPP

#include <tree/Component/Object.hpp>
#include <tree/Utility/Ticker.hpp>

namespace tree
{
    /**
     * An object which has a timed life.
     *
     * At the end of its lifetime, it should be destroyed.
     */
    class Expirable : virtual public Object
    {
    protected:
        Ticker expireTicker;

    public:
        /**
         * Constructor.
         */
        Expirable(unsigned int lifetime = 60);

        /**
         * Tick towards expiration.
         */
        void tickLifetime();

        /**
         * Checks if this object has expired.
         */
        bool isExpired() const;
    };
}

#endif
