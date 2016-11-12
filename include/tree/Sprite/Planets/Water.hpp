#ifndef TREESIMULATOR_SPRITE_PLANETS_WATER_HPP
#define TREESIMULATOR_SPRITE_PLANETS_WATER_HPP

#include <tree/Sprite/Sprite.hpp>
#include <tree/Resource/TextureSpace.hpp>
#include <tree/Resource/Shader.hpp>

namespace tree
{
    namespace sprite
    {
        class WaterPlanet : public Sprite
        {
            sf::CircleShape planetShape;
            sf::Color planetColor;
            TextureSpace textureSpace;

        public:
            WaterPlanet(float radius);

            void animate() override;
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        };
    }
}

#endif
