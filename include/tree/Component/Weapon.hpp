#ifndef TREESIMULATOR_COMPONENT_WEAPON_HPP
#define TREESIMULATOR_COMPONENT_WEAPON_HPP

#include <tree/Component.hpp>

namespace tree
{
    class Weapon
    : virtual public Drawable,
      virtual public Expirable,
      virtual public Physical
    {
    public:
        Weapon(unsigned int lifetime = 60);
        virtual void act(std::vector<Vector> &targets);
    };
}

#endif
