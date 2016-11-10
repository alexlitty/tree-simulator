#include <tree/Component/Physical.hpp>
#include <tree/Engine/Constant.hpp>
#include <tree/Utility/Collection.hpp>

// Enables physics.
void tree::Physical::enablePhysics()
{
    m_body->SetActive(true);
}

void tree::Physical::disablePhysics()
{
    m_body->SetActive(false);
}

// Create a body and add it to the physics system.
void tree::Physical::setBody(b2BodyDef &bodyDef)
{
    bodyDef.userData = this;
    
    // Delete old body, set new body.
    if (m_body != nullptr) {
        deleteBody();
    }
    m_body = tree::world.CreateBody(&bodyDef);
}

// Deletes the current body and removes it from the physics system.
void tree::Physical::deleteBody()
{
    if (m_body != nullptr) {
        tree::world.DestroyBody(m_body);
    }
}

// Constructor.
tree::Physical::Physical()
: m_body(nullptr)
{
    m_isPhysical = true;
}

// Destructor.
tree::Physical::~Physical()
{
    // Delete joints.
    for (auto joint : m_joints) {
        removeJoint(joint);
    }

    // Delete body, and all other dependent objects.
    deleteBody();
}

// Add a fixture.
b2Fixture* tree::Physical::addFixture(b2FixtureDef &fixtureDef)
{
    return m_body->CreateFixture(&fixtureDef);
}

// Updates the mass of this body.
void tree::Physical::updateMass()
{
    m_body->ResetMassData();
}

// Add a distance joint.
void tree::Physical::distanceJoint(Physical &other, Vector thisAnchor, Vector otherAnchor, bool localize)
{
    // Localize points.
    thisAnchor = m_body->GetLocalPoint(thisAnchor);
    otherAnchor = m_body->GetLocalPoint(otherAnchor);

    // Create joint.
    b2DistanceJointDef def;
    def.Initialize(m_body, other.m_body, thisAnchor, otherAnchor);
    def.frequencyHz = 0.0f;
    def.dampingRatio = 1.0f;
    b2Joint *joint = tree::world.CreateJoint(&def);

    // Track joint.
    trackJoint(joint);
    other.trackJoint(joint);
}

// Add a joint to be tracked.
void tree::Physical::trackJoint(b2Joint *joint)
{
    m_joints.push_back(joint);
}

// Removes a joint.
void tree::Physical::removeJoint(b2Joint *joint, bool fromOther)
{
    // Remove reference.
    tree::remove(m_joints, joint);

    // Other object has removed their reference. Destroy joint.
    if (fromOther) {
        tree::world.DestroyJoint(joint);
    }

    // Or, let other object remove joint.
    else {
        Physical *other = reinterpret_cast<Physical*>(
            joint->GetBodyA()->GetUserData()
        );

        if (other == this) {
            other = reinterpret_cast<Physical*>(
                joint->GetBodyB()->GetUserData()
            );
        }

        other->removeJoint(joint, true);
    }
}

// Handle a collision with another physical object.
void tree::Physical::onCollision(tree::Physical *other)
{

}

// Get mass.
float tree::Physical::getMass() const
{
    return m_body->GetMass();
}

// Get physical position.
tree::Vector tree::Physical::getPosition() const
{
    return m_body->GetWorldCenter();
}

// Get pixel position.
sf::Vector2f tree::Physical::getPixelPosition() const
{
    b2Vec2 result = tree::PIXELS_PER_METER * m_body->GetWorldCenter();
    return Vector(result);
}

// Sets position.
void tree::Physical::setPosition(Vector position)
{
    tree::Drawable::setPosition(position);
    m_body->SetTransform(position, this->getAngle().radians());
}

// Gets position, plus an angled distance.
tree::Vector tree::Physical::getAngledPosition(float magnitude, Angle angle) const
{
    Vector delta(
        this->getAngle() + angle,
        magnitude
    );

    return this->getPosition() + delta;
}

// Gets current angle.
tree::Angle tree::Physical::getAngle() const
{
    Angle angle;
    angle.radians(m_body->GetAngle());
    return angle;
}

// Sets current angle.
void tree::Physical::setAngle(Angle angle)
{
    tree::Drawable::setAngle(angle);

    bool originalValue = this->getFixedRotation();
    this->setFixedRotation(false);

    m_body->SetTransform(this->getPosition(), angle.radians());
    this->setFixedRotation(originalValue);
}

// Performs a rotation with default power.
void tree::Physical::rotate(bool direction)
{
    Angle angle;
    angle.radians(direction ? m_rotationPower : -m_rotationPower);
    this->rotate(angle);
}

// Performs a rotation.
void tree::Physical::rotate(tree::Angle angle)
{
    this->setAngle(
        this->getAngle() + angle
    );
}

// Gets fixed rotation.
bool tree::Physical::getFixedRotation() const
{
    return m_body->IsFixedRotation();
}

// Sets fixed rotation.
void tree::Physical::setFixedRotation(bool fixed)
{
    return m_body->SetFixedRotation(fixed);
}

// Gets current linear velocity.
tree::Vector tree::Physical::getLinearVelocity() const
{
    return m_body->GetLinearVelocity();
}

// Sets linear velocity.
void tree::Physical::setLinearVelocity(Vector velocity)
{
    m_body->SetLinearVelocity(velocity);
}

// Applies force to this object.
void tree::Physical::applyForce(const Vector force)
{
    m_totalForce += force;
    m_body->ApplyForceToCenter(force, true);
}

// Applies thrust to this object.
void tree::Physical::applyThrust(bool direction)
{
    m_currentThrustPower = direction ? m_thrustPower : -m_thrustPower;

    // Create force vector to apply.
    Vector force(
        this->getAngle(),
        m_currentThrustPower
    );

    // Apply force.
    m_body->ApplyForceToCenter(force, true);
}

// Whether this object is currently thrusting.
bool tree::Physical::isThrusting() const
{
    return m_currentThrustPower != 0.0f;
}

// Gets current thrusting power.
float tree::Physical::getCurrentThrust() const
{
    return m_currentThrustPower;
}

// Applies torque to this object.
void tree::Physical::applyTorque(bool direction)
{
    m_body->ApplyTorque(
        direction ? m_torquePower : -m_torquePower,
        true
    );
}

// Applies gravity from a gravity source.
void tree::Physical::applyGravity(Physical &other)
{
    this->applyGravity(&other);
}

// Applies gravity from a gravity source.
void tree::Physical::applyGravity(Physical *other)
{
    if (this == other || !other->createsGravity || !this->feelsGravity) {
        return;
    }

    // Directly on the source. Impossible to escape.
    float distance = this->getPosition().distance(other->getPosition());
    if (distance == 0.0f) {
        return;
    }

    // Calculate force magnitude.
    float magnitude = tree::GRAVITATIONAL_CONSTANT
                    * this->getMass()
                    * other->getMass()
                    / std::pow(distance, 2);

    // Create force vector.
    Vector force(
        (other->getPosition() - this->getPosition()).getAngle(),
        magnitude
    );

    // Apply force.
    this->applyForce(force);
}

// Gets the total force being applied next step.
tree::Vector tree::Physical::getTotalForce() const
{
    return m_totalForce;
}

// Prepares this object for another physics step.
void tree::Physical::prepare()
{
    m_currentThrustPower = 0.0f;
    m_totalForce.SetZero();
}

// Estimates the next linear velocity.
tree::Vector tree::Physical::estimateLinearVelocity() const
{
    Vector stepForce((1 / 120.0f) * m_totalForce);
    return this->getLinearVelocity() + stepForce;
}

// Gets the current physical transform.
sf::Transform tree::Physical::getPhysicalTransform() const
{
    sf::Transform transform;
    transform.translate(this->getPixelPosition());
    transform.rotate(this->getAngle().degrees());
    return transform;
}

// Transforms a local vector to a global vector.
tree::Vector tree::Physical::applyTransform(tree::Vector vector) const
{
    return this->getPhysicalTransform().transformPoint(vector);
}

// Adds the physical transform to a drawing transform.
void tree::Physical::addPhysicalTransform(sf::Transform &transform) const
{
    sf::Transform physicalTransform = this->getPhysicalTransform();
    transform.combine(physicalTransform);
}
