#include <tree/Component/Expirable.hpp>

// Constructor.
tree::Expirable::Expirable(unsigned int lifetime)
: m_expireLifetime(lifetime)
{
    m_isExpirable = true;
}

// Checks if this object has expired.
bool tree::Expirable::isExpired() const
{
    return static_cast<unsigned int>(m_expireClock.getElapsedTime().asMilliseconds()) >= m_expireLifetime;
}

// Action to occur upon expiration.
void tree::Expirable::expire(tree::Objects &objects)
{

}
