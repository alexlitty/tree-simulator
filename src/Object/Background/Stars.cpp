#include <tree/Object/Background/Stars.hpp>
#include <tree/Math/Random.hpp>

// Constructor.
tree::Background::Stars::Stars(unsigned int count, float initDistance)
: m_small(sf::Points, count),
  distance(initDistance)
{
    float min = -20, max = 20;
    int result;
    sf::Vector2f position;

    // Make Stars.
    for (unsigned int i = 0; i < count; i++) {

        // Determine position.
        position.x = tree::random(min, max);
        position.y = tree::random(min, max);
        m_small[i].position = position;

        // Determine color.
        result = tree::random(0, 255);
        m_small[i].color = sf::Color(result, result, result);
    }
    m_smallTransform.setOrigin(sf::Vector2f(0, 0));
}

// Sets where the view is looking.
void tree::Background::Stars::setViewTarget(sf::Vector2f target)
{
    m_smallTransform.setPosition(target);
    target.x /= -distance;
    target.y /= -distance;
    m_smallTransform.move(target);
}

// Draw the stars.
void tree::Background::Stars::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= m_smallTransform.getTransform();
    target.draw(m_small, states);
}
