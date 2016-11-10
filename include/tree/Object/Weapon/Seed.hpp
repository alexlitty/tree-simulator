#ifndef TREESIMULATOR_OBJECT_WEAPON_SEED
#define TREESIMULATOR_OBJECT_WEAPON_SEED

#include <tree/Component.hpp>
#include <tree/Math.hpp>

namespace tree
{
    namespace weapon
    {
        class Seed : virtual public Weapon
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
             * Act.
             */
            virtual void act(std::vector<Vector> &targets) override;

            /**
             * Draws the seed.
             */
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        };
    }
}

#endif
