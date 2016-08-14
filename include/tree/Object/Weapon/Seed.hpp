#ifndef TREESIMULATOR_OBJECT_WEAPON_SEED
#define TREESIMULATOR_OBJECT_WEAPON_SEED

#include <tree/Component.hpp>
#include <tree/Math.hpp>

namespace tree
{
    namespace weapon
    {
        class Seed : public Drawable, public Expirable, public Physical
        {
            sf::CircleShape shape;

        public:
            
            /**
             * Constructor.
             */
            Seed(Vector initialPoint, Vector initialVelocity);

            /**
             * Draws the seed.
             */
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        };
    }
}

#endif
