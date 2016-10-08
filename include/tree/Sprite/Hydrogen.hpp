#ifndef TREESIMULATOR_SPRITE_HYDROGEN
#define TREESIMULATOR_SPRITE_HYDROGEN

#include <tree/Sprite/Sprite.hpp>

namespace tree
{
    namespace sprite
    {
        class Hydrogen : public Sprite
        {
        public:
            void prepare() override;
            void animate() override;
        };
    }
}

#endif
