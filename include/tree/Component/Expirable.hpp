#ifndef TREESIMULATOR_COMPONENT_EXPIRABLE_HPP
#define TREESIMULATOR_COMPONENT_EXPIRABLE_HPP

#include <SFML/System.hpp>
#include <tree/Component/Object.hpp>

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
        // Clock used to track lifetime.
        sf::Clock m_expireClock;

        // Maximum lifetime of this object.
        unsigned int m_expireLifetime;

    public:
        /**
         * Constructor.
         *
         * Lifetime is in milliseconds.
         */
        Expirable(unsigned int lifetime = 1000);

        /**
         * Checks if this object has expired.
         */
        bool isExpired() const;

        /**
         * Action to occur upon expiration.
         */
        virtual void expire();
    };
}

#endif
