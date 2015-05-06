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
    class lifeform
    {
        uint32_t m_health_max;
        uint32_t m_health;

    public:
        /**
         * Constructor.
         */
        lifeform(uint32_t health_max = 1);

        /**
         * Retrieves maximum health.
         */
        uint32_t get_health_max() const;

        /**
         * Sets maximum health.
         */
        void set_health_max(uint32_t amount, bool fill = true);

        /**
         * Retrieves health.
         */
        uint32_t get_health() const;

        /**
         * Sets health.
         */
        void set_health(uint32_t amount);

        /**
         * Fills health to maximum.
         */
        void fill_health();

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
        bool is_dead() const;
    };
}

#endif
