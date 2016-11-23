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
    this->enemiesShocked.clear();
    this->shootThresholdTicker.tick();
}

// Shoots seeds.
void tree::Leaf::shoot(Angle angle, std::vector<tree::Lifeform*> &enemies, std::vector<tree::Weapon*> &weapons)
{
    //if (this->shootThresholdTicker.isMaxed()) {
    if (molecule == tree::Molecule::Oxygen) {
        Vector globalPosition = this->parent->applyTransform(this->position);
        Vector target;

        float nearestDistance = 0.0f;
        tree::Lifeform* nearestEnemy = nullptr;
        for (auto enemy : enemies) {
            if (this->enemiesShocked.count(enemy)) {
                continue;
            }

            float distance = globalPosition.distance(enemy->getPosition());
            if (nearestEnemy == nullptr || distance < nearestDistance) {
                nearestDistance = distance;
                nearestEnemy = enemy;
            }
        }

        if (nearestEnemy) {
            this->enemiesShocked.insert(nearestEnemy);
            target = nearestEnemy->getPosition();

            nearestEnemy->damage(1);
        }

        else {
            target = globalPosition + Vector(
                tree::random(0.0f, 20.0f),
                tree::random(0.0f, 20.0f)
            );
        }

        this->shootThresholdTicker.reset();
        tree::Weapon* electricity = new tree::weapon::Electricity(
            globalPosition,
            target
        );

        weapons.push_back(electricity);
    }

    else if (this->shootThresholdTicker.isMaxed()) {
        this->shootThresholdTicker.reset();

        Vector newPosition = this->parent->applyTransform(this->position);
        newPosition.x = (newPosition.x - 0.25f) + tree::random(0.0f, 0.5f);
        newPosition.y = (newPosition.y - 0.25f) + tree::random(0.0f, 0.5f);

        Vector localVelocity(angle, 250.0f);
        tree::weapon::Seed* seed = new tree::weapon::Seed(
            newPosition,
            localVelocity + this->parent->getLinearVelocity()
        );

        weapons.push_back(seed);
    }
}

// Draws leaf.
void tree::Leaf::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->vertices, states);
}
