#include <component/lifeform.hpp>

// Constructor.
tree::lifeform::lifeform(uint32_t health_max)
: m_health_max(health_max)
{
    fill_health();
}

// Retrieves maximum health.
uint32_t tree::lifeform::get_health_max() const
{
    return m_health_max;
}

// Sets maximum health.
void tree::lifeform::set_health_max(uint32_t amount, bool fill)
{
    m_health_max = amount;

    // Truncate health.
    if (m_health > m_health_max) {
        m_health = m_health_max;
    }

    // Fill health, if requested.
    else if (fill) {
        fill_health();
    }
}

// Retrieves health.
uint32_t tree::lifeform::get_health() const
{
    return m_health;
}

// Sets health.
void tree::lifeform::set_health(uint32_t amount)
{
    m_health = amount;
}

// Fills health to maximum.
void tree::lifeform::fill_health()
{
    m_health = m_health_max;
}

// Performs damage onto this lifeform.
void tree::lifeform::damage(uint32_t amount)
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

// Provides this lifeform with a certain amount of health.
void tree::lifeform::heal(uint32_t amount)
{
    // Overheal.
    if (amount >= (m_health_max - m_health)) {
        fill_health();
    }

    // Or, just heal normally.
    else
    {
        m_health += amount;
    }
}

// Retrieves the death status of this lifeform.
bool tree::lifeform::is_dead() const
{
    return (m_health == 0);
}
