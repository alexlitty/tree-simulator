#include <object/background/stars.hpp>
#include <math/random.hpp>

// Constructor.
tree::background::stars::stars(unsigned int count, float init_distance)
: m_small(sf::Points, count),
  distance(init_distance)
{
    float min = -1E4, max = 1E4;
    int result;
    sf::Vector2f position;

    // Make stars.
    for (unsigned int i = 0; i < count; i++) {

        // Determine position.
        position.x = tree::random(min, max);
        position.y = tree::random(min, max);
        m_small[i].position = position;

        // Determine color.
        result = tree::random(0, 255);
        m_small[i].color = sf::Color(result, result, result);
    }
    m_small_transform.setOrigin(sf::Vector2f(0, 0));
}

// Sets where the view is looking.
void tree::background::stars::setViewTarget(sf::Vector2f target)
{
    m_small_transform.setPosition(target);
    target.x /= -distance;
    target.y /= -distance;
    m_small_transform.move(target);
}

// Draw the stars.
void tree::background::stars::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= m_small_transform.getTransform();
    target.draw(m_small, states);
}
