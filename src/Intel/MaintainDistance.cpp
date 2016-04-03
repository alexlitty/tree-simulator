#include <tree/Component.hpp>
#include <tree/Math.hpp>

// Maintains a distance from a target position.
void tree::Intel::maintainDistance(tree::Vector target, float distance)
{
    float currentDistance = this->getPosition().distance(target);

    if (!tree::similar(currentDistance, distance, 5.0f)) {

        // Too close. Move farther away.
        if (currentDistance < distance) {

            // Get facing-angle opposite of target.
            /*float targetAngle = target.getAngle();
            targetAngle -= PI;*/

            // Generate facing-away vector.
            Angle pi;
            pi.radians(PI);

            Vector newTarget(
                this->getTotalForce().getAngle() - pi,
                1.0f
            );

            // Face away from target and thrust.
            this->faceTarget(newTarget);
        }

        // Too far away.
        else {

            // Get estimated velocity.
            b2Vec2 estimate = this->estimateLinearVelocity();
            float estimateLength = estimate.Length();

            // Check if we're already moving toward target.
            if (estimateLength > 10.0f) {

                float deltaAngle = this->getPosition().getAngle(target).radians();

                // We are. Do nothing.
                if (deltaAngle < PI_HALF && deltaAngle > -PI_HALF) {
                    return;
                }
            }

            // Move toward target.
            this->faceTarget(target);
        }

        // Apply thrust.
        this->applyThrust(true);
    }

    //--

    // Face away from total force.
    /*float angle = tree::Math::getAngle(this->getTotalForce()) - PI;
    b2Vec2 targetAngle = tree::Math::createVector(angle, 1.0f);
    this->faceTarget(targetAngle);

    // Calculate distance between target.
    float currentDistance = tree::Math::distance(
        this->getPosition(),
        target
    );

    // Thrust if necessary.
    if (tree::similar(angle, this->getAngle(), 0.2f)) {
        if (currentDistance < distance) {
            this->applyThrust(true);
        }
    }*/
}
