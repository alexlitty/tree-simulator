#ifndef TREESIMULATOR_OBJECT_PLANETCRUMB
#define TREESIMULATOR_OBJECT_PLANETCRUMB

#include <tree/Component.hpp>

namespace tree
{
    class PlanetCrumb : virtual public Drawable
    {
    protected:
        sf::CircleShape shape;

    public:

        /**
         * Constructor.
         */
        PlanetCrumb();

        /**
         * Draw this crumb.
         */
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}

#endif
