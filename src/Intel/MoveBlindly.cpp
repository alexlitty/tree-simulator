#include <tree/Component/Intel.hpp>
#include <tree/Math.hpp>

// Attempt to face a target.
void tree::Intel::faceTarget(Vector& target)
{
    Angle deltaAngle;
    deltaAngle.radians(
        this->getPosition().getAngle(target).radians() + PI
    );

    Angle angle = this->getAngle() - deltaAngle;

    if (!tree::similar(angle.degrees(), 0.0f, 20.0f)) {
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
