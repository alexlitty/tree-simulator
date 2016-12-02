#include <tree/Gui/Radar.hpp>
#include <tree/Math.hpp>

tree::Radar::Radar(std::vector<tree::Player*>& initPlayers)
: players(initPlayers),
  background(50.0f, 60),
  player(2.0f, 5)
{
    this->background.setFillColor(sf::Color(60, 60, 60, 125));
    this->background.setOutlineThickness(2.0f);
    this->background.setOutlineColor(sf::Color(120, 120, 120, 125));

    this->player.setFillColor(sf::Color::Green);
    tree::centerOrigin(this->player);
}

void tree::Radar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform = this->getTransform();
    target.draw(background, states);

    player.setPosition(50.0f, 50.0f);
    Vector delta = players[0]->getPosition();
    player.move(delta / 25.0f);
    target.draw(player, states);
}
