#ifndef TREESIMULATOR_OBJECT_WEAPON_SEED
#define TREESIMULATOR_OBJECT_WEAPON_SEED

#include <tree/Component.hpp>
#include <tree/Math.hpp>

namespace tree
{
    namespace weapon
    {
        class Seed
        : virtual public Drawable,
          virtual public Expirable,
          virtual public Physical,
          virtual public Weapon
        {
            sf::CircleShape shape;

        public:
            
            /**
             * Constructor.
             */
            Seed(Vector initialPoint, Vector initialVelocity);

            /**
             * Handle collisions.
             */
            void onCollision(Physical *other) override;

            /**
             * Draws the seed.
             */
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        };
    }
}

#endif
