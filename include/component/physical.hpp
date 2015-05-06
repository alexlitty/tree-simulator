#ifndef TREESIMULATOR_COMPONENT_PHYSICAL_HPP
#define TREESIMULATOR_COMPONENT_PHYSICAL_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    /**
     * A physical object in the game universe.
     */
    class physical
    {
        // Graphical transformation caused by physics.
        sf::Transformable m_physical_transform;

        // Current position.
        sf::Vector2f m_position;

        // Current speed.
        float m_speed_horizontal;
        float m_speed_vertical;

        // Current acceleration.
        float m_acceleration_horizontal;
        float m_acceleration_vertical;

    public:
        /**
         * Retrieves the graphical transformation caused by physics.
         */
        const sf::Transform& get_physical_transform() const;

        /**
         * Allow time to pass, letting this object move.
         */
        void pass_time(float seconds);

        /**
         * Move this object relative to its current position.
         */
        void move(float horizontal, float vertical);

        /**
         * Get and set position.
         */
        sf::Vector2f get_position() const;
        void set_position(sf::Vector2f position);

        /**
         * Get and set speed.
         */
        float get_speed_horizontal() const;
        float get_speed_vertical() const;
        void set_speed_horizontal(float amount);
        void set_speed_vertical(float amount);

        /**
         * Get and set acceleration.
         */
        float get_acceleration_horizontal() const;
        float get_acceleration_vertical() const;
        void set_acceleration_horizontal(float amount);
        void set_acceleration_vertical(float amount);

        /**
         * Perform acceleration.
         */
        void accelerate_horizontal(float amount);
        void accelerate_vertical(float amount);
    };
}

#endif
