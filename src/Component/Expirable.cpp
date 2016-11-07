#include <tree/Component.hpp>

// Constructor.
tree::Expirable::Expirable(unsigned int lifetime)
: expireTicker(lifetime)
{
    m_isExpirable = true;
}

// Tick towards expiration.
void tree::Expirable::tickLifetime()
{
    this->expireTicker.tick();
}

// Checks if this object has expired.
bool tree::Expirable::isExpired() const
{
    return this->expireTicker.isMaxed();
}
