#include <tree/Brush.hpp>
#include <tree/Math.hpp>
#include <tree/Resource/Shader.hpp>

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
