#ifndef TREESIMULATOR_PHYSICS_BOUNDING_BOX_HPP
#define TREESIMULATOR_PHYSICS_BOUNDING_BOX_HPP

#include "../../Component/Drawable.hpp"

namespace tree
{
    namespace Bounding
    {
        /**
         * A bounding box used in physics calculations.
         *
         * Not intended for drawing.
         */
        struct Box
        {
            // Local points.
            sf::Vector2f aOriginal;
            sf::Vector2f bOriginal;
            sf::Vector2f cOriginal;
            sf::Vector2f dOriginal;

            // Top-left point.
            sf::Vector2f a;

            // Top-right point.
            sf::Vector2f b;

            // Bottom-left point.
            sf::Vector2f c;

            // Bottom-right point.
            sf::Vector2f d;

            /**
             * Default constructor.
             */
            Box();

            /**
             * Constructor, from SFML rectangle.
             */
            Box(sf::FloatRect other);

            /**
             * Constructor, from individual points.
             */
            Box(sf::Vector2f& aInit, sf::Vector2f& bInit, sf::Vector2f& cInit, sf::Vector2f& dInit);

            /**
             * Returns the size of this box.
             */
            sf::Vector2f getSize() const;

            /**
             * Access the current points by index number.
             */
            sf::Vector2f& operator[](unsigned int index);
        };
    }
}

#endif
