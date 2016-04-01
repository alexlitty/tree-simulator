#include <tree/Object/Tree/Leaf.hpp>
#include <tree/Object/Weapon/Seed.hpp>

// Constructor.
tree::Leaf::Leaf()
: shape(1.0f, 5)
{
    this->shape.setFillColor(sf::Color::Red);
}

// Shoots seeds.
void tree::Leaf::shoot(tree::Stage &stage, Angle angle, Point currentVelocity)
{
    tree::weapon::Seed* seed = new tree::weapon::Seed(
        this->position,
        tree::Math::createVector(angle.GetRadians(), 5.0f) // @@@ add current
    );
    
    stage.add(seed);
}

// Draws leaf.
void tree::Leaf::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(this->position);
    target.draw(this->shape);
}
