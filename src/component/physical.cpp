#include <component/physical.hpp>

// Retrieves the graphical transformation caused by physics.
const sf::Transform& tree::physical::get_physical_transform() const
{
    return m_physical_transform.getTransform();
}

// Allow time to pass, letting this object move.
void tree::physical::pass_time(float seconds)
{
    move(m_acceleration_horizontal * seconds,
         m_acceleration_vertical * seconds);
}

// Move this object relative to its current position.
void tree::physical::move(float horizontal, float vertical)
{
    sf::Vector2f delta(horizontal, vertical);
    set_position(get_position() + delta);
}

// Get position.
sf::Vector2f tree::physical::get_position() const
{
    return m_position;
}

// Set position.
void tree::physical::set_position(sf::Vector2f position)
{
    m_position = position;
    m_physical_transform.setPosition(position);
}

// Get horizontal speed.
float tree::physical::get_speed_horizontal() const
{
    return m_speed_horizontal;
}

// Get vertical speed.
float tree::physical::get_speed_vertical() const
{
    return m_speed_vertical;
}

// Set horizontal speed.
void tree::physical::set_speed_horizontal(float amount)
{
    m_speed_horizontal = amount;
}

// Set vertical speed.
void tree::physical::set_speed_vertical(float amount)
{
    m_speed_vertical = amount;
}

// Get horizontal acceleration.
float tree::physical::get_acceleration_horizontal() const
{
    return m_acceleration_horizontal;
}

// Get vertical acceleration.
float tree::physical::get_acceleration_vertical() const
{
    return m_acceleration_vertical;
}

// Set horizontal acceleration.
void tree::physical::set_acceleration_horizontal(float amount)
{
    m_acceleration_horizontal = amount;
}

// Set vertical speed.
void tree::physical::set_acceleration_vertical(float amount)
{
    m_acceleration_vertical = amount;
}

// Perform horizontal acceleration.
void tree::physical::accelerate_horizontal(float amount)
{
    set_acceleration_horizontal(get_acceleration_horizontal() + amount);
}

// Perform vertical acceleration.
void tree::physical::accelerate_vertical(float amount)
{
    set_acceleration_vertical(get_acceleration_vertical() + amount);
}
