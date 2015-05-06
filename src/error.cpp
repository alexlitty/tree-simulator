#include <error.hpp>

// Constructor.
tree::error::error(const char* message)
: m_message(message)
{
    
}

// Returns the explanatory string.
const char* tree::error::what() const noexcept(true)
{
    return m_message;
}
