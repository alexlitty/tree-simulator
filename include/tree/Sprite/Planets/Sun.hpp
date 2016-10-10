#ifndef TREESIMULATOR_SPRITE_PLANETS_SUN
#define TREESIMULATOR_SPRITE_PLANETS_SUN

#include <tree/Sprite/Sprite.hpp>

namespace tree
{
    namespace sprite
    {
        class Sun : public Sprite
        {
            sf::CircleShape planetShape;
            sf::Color planetColor;

        public:
            Sun(float radius);

            void animate() override;

            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        };
    }
}

#endif
