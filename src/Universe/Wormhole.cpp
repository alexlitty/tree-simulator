#include <tree/Universe/Wormhole.hpp>

// Constructor.
tree::Wormhole::Wormhole()
: timer(60)
{
    test.setRadius(15.0f);
    test.setOutlineThickness(5.0f);
    tree::centerOrigin(test);

    test.setPosition(tree::VectorZero);
    test.setFillColor(sf::Color::Black);
    test.setOutlineColor(sf::Color::Green);
}

// Animate the wormhole.
bool tree::Wormhole::act()
{
    return this->timer.tick();
}

// Draw the wormhole.
void tree::Wormhole::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    float scale = 10.0f * (1.0f + this->timer.percent());
    states.transform.scale(scale, scale);
    target.draw(test, states);
}
