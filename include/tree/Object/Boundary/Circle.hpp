#ifndef TREESIMULATOR_OBJECT_BOUNDARY_CIRCLE
#define TREESIMULATOR_OBJECT_BOUNDARY_CIRCLE

#include <tree/Component.hpp>

namespace tree
{
    namespace boundary
    {
        class Circle : virtual public Physical
        {
            sf::CircleShape shape;

        public:
            Circle(float radius);
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        };
    }
}

#endif
