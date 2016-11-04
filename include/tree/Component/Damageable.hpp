#ifndef TREESIMULATOR_COMPONENT_DAMAGEABLE_HPP
#define TREESIMULATOR_COMPONENT_DAMAGEABLE_HPP

#include <tree/Component/Object.hpp>

namespace tree
{
    class Damageable : virtual public Object
    {
    protected:
        unsigned int m_damage = 0;
        unsigned int m_maxDamage = 0;

    public:
        Damageable();

        void setMaxDamage(unsigned int amount);
        unsigned int getHealth() const;
        bool isDestroyed() const;

        void damage(unsigned int amount);
        void heal(unsigned int amount);
    };
}

#endif
