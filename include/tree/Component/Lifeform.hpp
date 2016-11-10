#ifndef TREESIMULATOR_COMPONENT_LIFEFORM_HPP
#define TREESIMULATOR_COMPONENT_LIFEFORM_HPP

#include <cstdint>
#include <tree/Component/Physical.hpp>
#include <tree/Component/Damageable.hpp>

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
    class Lifeform
    : virtual public Physical,
      virtual public Damageable
    {
        Faction m_faction;

    public:
        /**
         * Constructor.
         */
        Lifeform(Faction faction, unsigned int maxDamage = 1);

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
         * Act.
         */
        virtual void act();
    };
}

#endif
