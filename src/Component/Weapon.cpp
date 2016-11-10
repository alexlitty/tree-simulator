#include <tree/Component/Weapon.hpp>

tree::Weapon::Weapon(unsigned int lifetime)
: tree::Expirable::Expirable(lifetime)
{
    m_isWeapon = true;
}

void tree::Weapon::act(std::vector<Vector> &targets)
{

}
