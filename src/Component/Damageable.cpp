#include <tree/Component/Damageable.hpp>

tree::Damageable::Damageable()
{
    this->m_isDamageable = true;
}

void tree::Damageable::setMaxDamage(unsigned int amount)
{
    this->m_maxDamage = amount;
    this->damage(0);
}

unsigned int tree::Damageable::getHealth() const
{
    return this->m_maxDamage - this->m_damage;
}

bool tree::Damageable::isDestroyed() const
{
    return this->m_damage == this->m_maxDamage;
}

void tree::Damageable::damage(unsigned int amount)
{
    this->m_damage += amount;
    if (this->m_damage > this->m_maxDamage) {
        this->m_damage = this->m_maxDamage;
    }
}

void tree::Damageable::heal(unsigned int amount)
{
    if (amount >= this->m_damage) {
        this->m_damage = 0;
    }

    else {
        this->m_damage -= amount;
    }
}
