#ifndef TREESIMULATOR_BACKGROUND_STARS_HPP
#define TREESIMULATOR_BACKGROUND_STARS_HPP

#include <vector>
#include <SFML/Graphics.hpp>

#include "../../Component/Drawable.hpp"

namespace tree
{
    namespace Background
    {
        class Stars : public Drawable
        {
            sf::Transformable m_smallTransform;
            sf::VertexArray m_small;

        public:

            // Distance from the camera.
            float distance;

            /**
             * Constructor.
             */
            Stars(unsigned int count, float initDistance);

            /**
             * Sets where the view is looking.
             */
            void setViewTarget(sf::Vector2f target);

            /**
             * Draw the stars.
             */
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        };
    }
}

#endif
