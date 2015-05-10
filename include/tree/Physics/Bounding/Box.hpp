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
            Box(sf::FloatRect& other);

            /**
             * Constructor, from individual points.
             */
            Box(sf::Vector2f& aInit, sf::Vector2f& bInit, sf::Vector2f& cInit, sf::Vector2f& dInit);

            /**
             * Returns the size of this box.
             */
            sf::Vector2f getSize() const
            {
                return sf::Vector2f(b.x - a.x, d.y - b.y);
            }
        };
    }
}

#endif
