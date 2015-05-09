#include <tree/Component/Lifeform.hpp>

// Constructor.
tree::Lifeform::Lifeform(uint32_t health_max)
: m_healthMax(health_max)
{
    fillHealth();
}

// Retrieves maximum health.
uint32_t tree::Lifeform::getHealthMax() const
{
    return m_healthMax;
}

// Sets maximum health.
void tree::Lifeform::setHealthMax(uint32_t amount, bool fill)
{
    m_healthMax = amount;

    // Truncate health.
    if (m_health > m_healthMax) {
        m_health = m_healthMax;
    }

    // Fill health, if requested.
    else if (fill) {
        fillHealth();
    }
}

// Retrieves health.
uint32_t tree::Lifeform::getHealth() const
{
    return m_health;
}

// Sets health.
void tree::Lifeform::setHealth(uint32_t amount)
{
    m_health = amount;
}

// Fills health to maximum.
void tree::Lifeform::fillHealth()
{
    m_health = m_healthMax;
}

// Performs damage onto this Lifeform.
void tree::Lifeform::damage(uint32_t amount)
{
    // Overkill.
    if (amount >= m_health) {
        m_health = 0;
    }

    // Or, just reduce health.
    else
    {
        m_health -= amount;
    }
}

// Provides this Lifeform with a certain amount of health.
void tree::Lifeform::heal(uint32_t amount)
{
    // Overheal.
    if (amount >= (m_healthMax - m_health)) {
        fillHealth();
    }

    // Or, just heal normally.
    else
    {
        m_health += amount;
    }
}

// Retrieves the death status of this Lifeform.
bool tree::Lifeform::isDead() const
{
    return (m_health == 0);
}
