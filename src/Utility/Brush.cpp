#include <tree/Math.hpp>
#include <tree/Resource/Shader.hpp>
#include <tree/Utility/Brush.hpp>

tree::palette tree::brush::palette = tree::palette::random;

void tree::brush::noise(sf::RenderTarget *target)
{
    sf::Vector2f size = sf::Vector2f(target->getSize());

    // Shape to cover entire target.
    sf::VertexArray cover(sf::Quads, 4);
    cover[0].position = sf::Vector2f(0.0f, 0.0f);
    cover[1].position = sf::Vector2f(size.x, 0.0f);
    cover[2].position = sf::Vector2f(size.x, size.y);
    cover[3].position = sf::Vector2f(0.0f, size.y);

    sf::RenderStates states;
    states.shader = &tree::Shader::NoiseSimple;
    target->draw(cover, states);
}

void tree::brush::spots(sf::RenderTarget *target, unsigned int count, float minRadius, float maxRadius)
{
    sf::Color color;
    sf::CircleShape circle;
    circle.setPointCount(60);
    sf::RenderStates states;
    states.blendMode = sf::BlendAlpha;

    sf::Vector2u size = target->getSize();
    for (unsigned int i = 0; i < count; i++) {
        circle.setRadius(
            tree::random(minRadius, maxRadius)
        );
        circle.setPosition(
            tree::random(-maxRadius, size)
        );
        color = tree::paletteColor(tree::brush::palette);
        color.a = tree::random(10, 20);
        circle.setFillColor(color);

        target->draw(circle, states);
    }
}

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
    tree::Math::centerOrigin(test);
    test.setPosition(size.x / 2, size.y / 2);
    target->draw(test, states);
}
