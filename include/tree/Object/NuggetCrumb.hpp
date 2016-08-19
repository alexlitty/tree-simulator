#ifndef TREESIMULATOR_OBJECT_NUGGETCRUMB
#define TREESIMULATOR_OBJECT_NUGGETCRUMB

#include <tree/Component.hpp>

namespace tree
{
    class NuggetCrumb : virtual public Drawable
    {
    protected:
        sf::CircleShape shape;

    public:

        /**
         * Constructor.
         */
        NuggetCrumb();

        /**
         * Moves the crumb towards a vector.
         */
        void moveToward(tree::Vector vector);

        /**
         * Draw this crumb.
         */
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}

#endif
