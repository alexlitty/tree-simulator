#include <tree/Component/Intel.hpp>
#include <tree/Math.hpp>

// Attempt to face a target.
void tree::Intel::faceTarget(Vector& target)
{
    Angle deltaAngle = this->getPosition().getAngle(target);

    Angle angle = this->getAngle() - deltaAngle;
    if (!tree::similar(angle.radians(), 0.0f, 0.1f)) {
        if (angle.radians() < 0.0f) {
            this->rotate(true);
        } else {
            this->rotate(false);
        }
    }
}

// Blindly move toward a target position.
void tree::Intel::moveBlindly(Vector &target)
{
    this->faceTarget(target);
    this->applyThrust(true);
}
