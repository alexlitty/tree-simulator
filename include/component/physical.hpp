#ifndef TREESIMULATOR_COMPONENT_PHYSICAL_HPP
#define TREESIMULATOR_COMPONENT_PHYSICAL_HPP

namespace tree
{
    class object;
}

#include <vector>
#include <SFML/Graphics.hpp>

namespace tree
{
    /**
     * A physical object in the game universe.
     *
     * Angles are represented in degrees. Positive angular values are clockwise.
     */
    class physical
    {
        // Graphical transformation caused by physics.
        sf::Transformable m_physical_transform;

        // Current position.
        sf::Vector2f m_position;

        // Rotational angle.
        float m_rotation;

    public:
        // Mass in kilograms.
        float mass;

        // Velocity in meters per second.
        sf::Vector2f velocity;

        // Acceleration in meters per second squared.
        sf::Vector2f acceleration;

        // Rotational speed.
        float rotation_speed;

        // Rotational speed limit.
        float rotation_speed_max;

        // Rotational acceleration.
        float rotation_acceleration;

        /**
         * Constructor.
         */
        physical();

        /**
         * Retrieves the graphical transformation caused by physics.
         */
        const sf::Transform& get_physical_transform() const;

        /**
         * Allows time to pass, letting physics change this object.
         */
        void pass_time(float seconds, std::vector<physical*>& objects);

        /**
         * Move this object relative to its current position.
         */
        void move(sf::Vector2f& vector);

        /**
         * Gets and sets position.
         */
        sf::Vector2f get_position() const;
        void set_position(sf::Vector2f& position);

        /**
         * Gets and sets rotation.
         */
        float get_rotation() const;
        void set_rotation(float magnitude);

        /**
         * Perform rotation.
         */
        void rotate(float magnitude);
    };
}

#endif
