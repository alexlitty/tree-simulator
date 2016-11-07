#include <tree/Universe/Wormhole.hpp>

// Constructor.
tree::Wormhole::Wormhole()
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
    return true;
}

// Draw the wormhole.
void tree::Wormhole::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(test, states);
}
