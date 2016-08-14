#include <tree/Object/Tree/Leaf.hpp>
#include <tree/Object/Weapon/Seed.hpp>

// Constructor.
tree::Leaf::Leaf(Physical* _parent)
: parent(_parent),
  shape(1.0f, 5)
{
    this->shape.setFillColor(sf::Color::Red);
    tree::centerOrigin(this->shape);
}

// Shoots seeds.
void tree::Leaf::shoot(std::vector<tree::weapon::Seed*> &seeds, Angle angle)
{
    Vector newPosition = this->position + this->parent->getPosition();
    newPosition.x = (newPosition.x - 0.25f) + tree::random(0.0f, 0.5f);
    newPosition.y = (newPosition.y - 0.25f) + tree::random(0.0f, 0.5f);

    Vector localVelocity(angle, 250.0f);
    tree::weapon::Seed* seed = new tree::weapon::Seed(
        newPosition,
        localVelocity + this->parent->getLinearVelocity()
    );

    seeds.push_back(seed);
}

// Draws leaf.
void tree::Leaf::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(this->position);
    target.draw(this->shape, states);
}
