#include <tree/Brush.hpp>
#include <tree/Math.hpp>

void tree::brush::lines(sf::RenderTarget *target)
{
    sf::VertexArray line(sf::LinesStrip, 20);
    line[0].color = line[1].color = sf::Color::Green;
    sf::RenderStates states;
    for (unsigned int i = 0; i < 20; i++) {
        line[i].color = sf::Color::Green;
    }

    sf::Vector2f size = sf::Vector2f(target->getSize());
    for (float current = 0.0f; current < size.x; current += 20.0f) {
        line[0].position.x = current;
        line[0].position.y = 0.0f;
        float inc = current / 20.0f;

        for (unsigned int i = 1; i < 20; i++) {
            line[i].position.x = line[i - 1].position.x - inc;
            line[i].position.y = line[i - 1].position.y + inc;
        }
        target->draw(line, states);
    }

    for (float current = size.x; current >= 0; current -= 20.0f) {
        line[0].position.x = size.x;
        line[0].position.y = current;
        float inc = (size.x - current) / 20.0f;

        for (unsigned int i = 1; i < 20; i++) {
            line[i].position.x = line[i - 1].position.x - inc;
            line[i].position.y = line[i - 1].position.y + inc;
        }
        target->draw(line, states);
    }
    sf::CircleShape test(25.0f, 60);
    test.setFillColor(sf::Color::Blue);
    tree::centerOrigin(test);
    test.setPosition(size.x / 2, size.y / 2);
    target->draw(test, states);
}
