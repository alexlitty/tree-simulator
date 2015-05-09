#include <tree/Engine/Error.hpp>

// Constructor.
tree::Error::Error(const char* message)
: m_message(message)
{
    
}

// Returns the explanatory string.
const char* tree::Error::what() const noexcept(true)
{
    return m_message;
}
