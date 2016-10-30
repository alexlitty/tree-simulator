#ifndef TREESIMULATOR_COMPONENT_LIFEFORM_HPP
#define TREESIMULATOR_COMPONENT_LIFEFORM_HPP

#include <cstdint>
#include <tree/Component/Physical.hpp>

namespace tree
{
    /**
     * Factions of lifeforms.
     */
    enum class Faction
    {
        none,
        wood,
        beaver
    };

    /**
     * Levels of friendliness.
     */
    enum class Opinion
    {
        neutral,
        friendly,
        hostile
    };

    /**
     * An object with life.
     *
     * Has health properties, which implies living and death conditions.
     */
    class Lifeform : virtual public Physical, virtual public Drawable
    {
        uint32_t m_healthMax;
        uint32_t m_health;

        Faction m_faction;

    public:
        /**
         * Constructor.
         */
        Lifeform(Faction faction, uint32_t health_max = 1);

        /**
         * Checks the opinion between two lifeforms.
         */
        Opinion getOpinion(Lifeform &other) const;

        /**
         * Quickly checks friendliness.
         */
        bool isFriendly(Lifeform &other) const;

        /**
         * Quickly checks hostility.
         */
        bool isHostile(Lifeform &other) const;

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

        /**
         * Act.
         */
        virtual void act();
    };
}

#endif
