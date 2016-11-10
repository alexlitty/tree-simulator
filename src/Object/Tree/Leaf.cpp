#include <tree/Object/Tree/Leaf.hpp>
#include <tree/Object/Weapon/Electricity.hpp>
#include <tree/Object/Weapon/Seed.hpp>

// Constructor.
tree::Leaf::Leaf(Physical* _parent, Vector _position, Molecule _molecule)
: parent(_parent),
  molecule(_molecule),
  shootThresholdTicker(tree::random(5, 15)),
  position(_position)
{
    Vector tipPosition = this->position + Vector(
        tree::random(1, 2),
        tree::random(1, 2)
    );

    this->vertices.setPrimitiveType(sf::TrianglesFan);
    this->vertices.append(position.center(tipPosition));
    tree::makeArc(this->vertices, this->position, tipPosition, 1.0f, tree::NormalDistribution);
    tree::makeArc(this->vertices, tipPosition, this->position, 1.0f, tree::NormalDistribution);
}

// Act.
void tree::Leaf::act()
{
    this->shootThresholdTicker.tick();
}

// Shoots seeds.
void tree::Leaf::shoot(Angle angle, std::vector<tree::Lifeform*> &enemies, std::vector<tree::Weapon*> &weapons)
{
    if (this->shootThresholdTicker.isMaxed()) {
        Vector globalPosition = this->parent->applyTransform(this->position);

        this->shootThresholdTicker.reset();
        tree::Weapon* electricity = new tree::weapon::Electricity(
            globalPosition,
            globalPosition + Vector(5.0f, 5.0f)
        );

        weapons.push_back(electricity);
    }
    return;
    /*if (this->shootThresholdTicker.isMaxed()) {
        this->shootThresholdTicker.reset();

        Vector newPosition = this->parent->applyPhysicalTransform(this->position);
        newPosition.x = (newPosition.x - 0.25f) + tree::random(0.0f, 0.5f);
        newPosition.y = (newPosition.y - 0.25f) + tree::random(0.0f, 0.5f);

        Vector localVelocity(angle, 250.0f);
        tree::weapon::Seed* seed = new tree::weapon::Seed(
            newPosition,
            localVelocity + this->parent->getLinearVelocity()
        );

        weapons.push_back(seed);
    }*/
}

// Draws leaf.
void tree::Leaf::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->vertices, states);
}
