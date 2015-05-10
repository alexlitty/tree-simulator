#ifndef TREESIMULATOR_COMPONENT_PHYSICAL_HPP
#define TREESIMULATOR_COMPONENT_PHYSICAL_HPP

#include <vector>
#include <SFML/Graphics.hpp>

namespace tree
{
    /**
     * A Physical object in the game universe.
     *
     * Angles are represented in degrees. Positive angular values are clockwise.
     */
    class Physical
    {
        // Graphical transformation caused by physics.
        sf::Transformable m_physicalTransform;

        // Current position.
        sf::Vector2f m_position;

        // Rotational angle.
        float m_rotation;

    public:
        // Mass in kilograms.
        float mass;

        // Velocity in meters per second.
        sf::Vector2f velocity;

        // Acceleration to be applied in this tick.
        sf::Vector2f acceleration;

        // Rotational speed.
        float rotationSpeed;

        // Rotational speed limit.
        float rotationSpeedMax;

        // Rotational acceleration to be applied in this tick.
        float rotationAcceleration;

        /**
         * Constructor.
         */
        Physical();

        /**
         * Retrieves the graphical transformation caused by physics.
         */
        const sf::Transform& getPhysicalTransform() const;

        /**
         * Allows time to pass, letting physics change this object.
         */
        void passTime(float seconds, std::vector<Physical*>& objects);

        /**
         * Position methods.
         */
        sf::Vector2f getPosition() const;
        void setPosition(sf::Vector2f& position);
        void move(sf::Vector2f& vector);
        void accelerate(sf::Vector2f& vector);

        /**
         * Rotation methods.
         */
        float getRotation() const;
        void setRotation(float magnitude);
        void rotate(float magnitude);
    };
}

#endif
