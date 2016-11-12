#include <tree/Sprite/Planets/Water.hpp>
#include <tree/Math.hpp>

// Constructor.
tree::sprite::WaterPlanet::WaterPlanet(float radius)
: textureSpace(radius * 2, (radius * 2) + 25.0f)
{
    sf::RectangleShape textureShape(sf::Vector2f(radius * 2, 25.0f));
    textureShape.setFillColor(sf::Color::Red);

    this->textureSpace.texture->clear();
    this->textureSpace.texture->draw(textureShape);
    this->textureSpace.texture->display();
    textureShape.setFillColor(sf::Color::Blue);
    textureShape.move(sf::Vector2f(0.0f, 25.0f));
    this->textureSpace.texture->draw(textureShape);
    this->textureSpace.texture->display();
    this->textureSpace.assign(this->planetShape);

    this->planetShape.setRadius(radius - 1.0f);
    this->planetShape.setPointCount(60);
    tree::centerOrigin(this->planetShape);

    this->planetColor = sf::Color(
        tree::random(10, 50),
        tree::random(0, 150),
        tree::random(150, 225)
    );
    this->planetShape.setFillColor(this->planetColor);
}

void tree::sprite::WaterPlanet::animate()
{

}

void tree::sprite::WaterPlanet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.shader = &tree::Shader::Fragment::Test;
    target.draw(this->planetShape, states);
}
