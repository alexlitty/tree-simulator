#ifndef TREESIMULATOR_COMPONENT_LIFEFORM_HPP
#define TREESIMULATOR_COMPONENT_LIFEFORM_HPP

#include <cstdint>

namespace tree
{
    /**
     * An object with life.
     *
     * Has health properties, which implies living and death conditions.
     */
    class Lifeform
    {
        uint32_t m_healthMax;
        uint32_t m_health;

    public:
        /**
         * Constructor.
         */
        Lifeform(uint32_t health_max = 1);

        /**
         * Retrieves maximum health.
         */
        uint32_t getHealthMax() const;

        /**
         * Sets maximum health.
         */
        void setHealthMax(uint32_t amount, bool fill = true);

        /**
         * Retrieves health.
         */
        uint32_t getHealth() const;

        /**
         * Sets health.
         */
        void setHealth(uint32_t amount);

        /**
         * Fills health to maximum.
         */
        void fillHealth();

        /**
         * Performs damage onto this lifeform.
         */
        void damage(uint32_t amount);

        /**
         * Provides this lifeform with a certain amount of health.
         */
        void heal(uint32_t amount);

        /**
         * Retrieves the death status of this lifeform.
         */
        bool isDead() const;
    };
}

#endif
