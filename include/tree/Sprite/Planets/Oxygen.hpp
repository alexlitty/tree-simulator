#ifndef TREESIMULATOR_SPRITE_PLANETS_OXYGEN_HPP
#define TREESIMULATOR_SPRITE_PLANETS_OXYGEN_HPP

#include <tree/Sprite/Sprite.hpp>

namespace tree
{
    namespace sprite
    {
        class OxygenPlanet : public Sprite
        {
            sf::CircleShape planetShape;
            sf::Color planetColor;

        public:
            OxygenPlanet(float radius);

            void animate() override;
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        };
    }
}

#endif
