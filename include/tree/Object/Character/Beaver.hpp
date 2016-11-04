#ifndef TREESIMULATOR_OBJECT_CHARACTER_BEAVER
#define TREESIMULATOR_OBJECT_CHARACTER_BEAVER

#include <tree/Component.hpp>
#include <tree/Object/Player.hpp>

namespace tree
{
    namespace character
    {
        class Beaver
        : virtual public Drawable,
          virtual public Intel,
          virtual public Lifeform,
          virtual public Damageable
        {
            Players players;
            mutable sf::RectangleShape m_tempShape;

        public:

            // Constructor.
            Beaver(Players &_players, b2Vec2 position);

            // Handle collisions.
            void onCollision(Physical *other) override;

            // Be a beaver.
            void act() override;

            // Draw beaver.
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        };
    }
}

#endif
