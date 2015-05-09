#ifndef TREESIMULATOR_BACKGROUND_STARS_HPP
#define TREESIMULATOR_BACKGROUND_STARS_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "../../component/drawable.hpp"

namespace tree
{
    namespace background
    {
        class stars : public tree::drawable
        {
            sf::Transformable m_small_transform;
            sf::VertexArray m_small;

        public:

            // Distance from the camera.
            float distance;

            /**
             * Constructor.
             */
            stars(unsigned int count, float init_distance);

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
