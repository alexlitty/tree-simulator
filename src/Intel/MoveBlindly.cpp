#include <tree/Component/Intel.hpp>
#include <tree/Math.hpp>

// Attempt to face a target.
void tree::Intel::faceTarget(b2Vec2 &target)
{
    float deltaAngle = tree::Math::getAngle(
        target - this->getPosition()
    );

    if (deltaAngle < 0) {
        this->applyTorque(false);
    } else {
        this->applyTorque(true);
    }
}

// Blindly move toward a target position.
void tree::Intel::moveBlindly(b2Vec2 &target)
{
    this->faceTarget(target);
    this->applyThrust(true);
}
