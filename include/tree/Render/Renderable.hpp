#pragma once

#include <SFML/Graphics.hpp>

namespace tree
{
    namespace render
    {
        class Renderable
        {
        public:
            void render(sf::RenderTarget& target, sf::RenderStates states);
        };
    }
}
