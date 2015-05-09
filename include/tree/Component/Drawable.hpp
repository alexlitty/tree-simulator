#ifndef TREESIMULATOR_COMPONENT_DRAWABLE_HPP
#define TREESIMULATOR_COMPONENT_DRAWABLE_HPP

#include <SFML/Graphics.hpp>

namespace tree
{
    class Drawable : public sf::Drawable
    {
    public:
        /**
         * Make the draw method public instead of protected.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    };
}

#endif
