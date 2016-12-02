#ifndef TREESIMULATOR_GUI_RADAR_HPP
#define TREESIMULATOR_GUI_RADAR_HPP

#include <tree/Component.hpp>
#include <tree/Object/Player.hpp>

namespace tree
{
    class Radar : virtual public Drawable
    {
        std::vector<Player*>& players;
        sf::CircleShape background;
        mutable sf::CircleShape player;

    public:
        Radar(std::vector<Player*>& initPlayers);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif
