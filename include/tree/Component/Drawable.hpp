#ifndef TREESIMULATOR_COMPONENT_DRAWABLE_HPP
#define TREESIMULATOR_COMPONENT_DRAWABLE_HPP

#include <SFML/Graphics.hpp>
#include <tree/Component/Object.hpp>

namespace tree
{
    class Drawable : virtual public Object, public sf::Drawable
    {
        unsigned char m_alpha;

    public:
        /**
         * Constructor.
         */
        Drawable();

        /**
         * Make the draw method public instead of protected.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    };
}

#endif
