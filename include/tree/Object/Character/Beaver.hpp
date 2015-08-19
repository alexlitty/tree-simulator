#ifndef TREESIMULATOR_OBJECT_CHARACTER_BEAVER
#define TREESIMULATOR_OBJECT_CHARACTER_BEAVER

#include <tree/Component.hpp>

namespace tree
{
    namespace character
    {
        class Beaver
        : virtual public Drawable,
          virtual public Intel,
          virtual public Lifeform
        {
            sf::RectangleShape m_tempShape;

        public:

            // Constructor.
            Beaver(b2Vec2 position);

            // Be a beaver.
            bool act(tree::Objects &objects) override;

            // Draw beaver.
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        };
    }
}

#endif
