#ifndef TREESIMULATOR_OBJECT_WEAPON_ELECTRICITY_HPP
#define TREESIMULATOR_OBJECT_WEAPON_ELECTRICITY_HPP

#include <tree/Component.hpp>

namespace tree
{
    namespace weapon
    {
        class Electricity : virtual public Weapon
        {
            sf::VertexArray vertices;

        public:
            Electricity(Vector start, Vector end);

            virtual void act(std::vector<Vector> &targets) override;
            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        };
    }
}

#endif
