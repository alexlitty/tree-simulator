#include <tree/Component/Intel.hpp>
#include <tree/Math.hpp>

// Attempt to face a target.
void tree::Intel::faceTarget(b2Vec2 &target)
{
    float deltaAngle = tree::getAngle(
        this->getPosition(), target
    );

    float angle = tree::angle(this->getAngle() - deltaAngle);
    if (!tree::similar(angle, 0.0f, 0.1f)) {
        if (angle < 0.0f) {
            this->rotate(true);
        } else {
            this->rotate(false);
        }
    }
}

// Blindly move toward a target position.
void tree::Intel::moveBlindly(b2Vec2 &target)
{
    this->faceTarget(target);
    this->applyThrust(true);
}
