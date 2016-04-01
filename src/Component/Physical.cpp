#include <tree/Component/Physical.hpp>
#include <tree/Engine/Constant.hpp>
#include <tree/Math/Geometry.hpp>
#include <tree/Math/Trigonometry.hpp>
#include <tree/Math/Vector.hpp>
#include <tree/Utility/Collection.hpp>

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
void tree::Physical::distanceJoint(Physical &other, b2Vec2 thisAnchor, b2Vec2 otherAnchor, bool localize)
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
void tree::Physical::onCollision(tree::Physical &other)
{

}

// Get mass.
float tree::Physical::getMass() const
{
    return m_body->GetMass();
}

// Get physical position.
b2Vec2 tree::Physical::getPosition() const
{
    return m_body->GetWorldCenter();
}

// Get pixel position.
sf::Vector2f tree::Physical::getPixelPosition() const
{
    return tree::Math::vector(
        tree::PIXELS_PER_METER * m_body->GetWorldCenter()
    );
}

// Sets physical position.
void tree::Physical::setPosition(b2Vec2 pos)
{
    m_body->SetTransform(pos, this->getAngle());
}

// Gets position, plus an angled distance.
b2Vec2 tree::Physical::getAngledPosition(float magnitude, float angle) const
{
    return this->getPosition() + tree::Math::createVector(
        this->getAngle() + angle, magnitude
    );
}

// Gets current angle.
float tree::Physical::getAngle() const
{
    return tree::angle(m_body->GetAngle());
}

// Sets current angle.
void tree::Physical::setAngle(float angle)
{
    angle = tree::angle(angle);
    bool originalValue = this->getFixedRotation();
    this->setFixedRotation(false);
    m_body->SetTransform(this->getPosition(), angle);
    this->setFixedRotation(originalValue);
}

// Performs a rotation with default power.
void tree::Physical::rotate(bool direction)
{
    this->rotate(
        direction ? m_rotationPower : -m_rotationPower
    );
}

// Performs a rotation.
void tree::Physical::rotate(float angle)
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
b2Vec2 tree::Physical::getLinearVelocity() const
{
    return m_body->GetLinearVelocity();
}

// Sets linear velocity.
void tree::Physical::setLinearVelocity(b2Vec2 velocity)
{
    m_body->SetLinearVelocity(velocity);
}

// Applies force to this object.
void tree::Physical::applyForce(const b2Vec2 force)
{
    m_totalForce += force;
    m_body->ApplyForceToCenter(force, true);
}

// Applies thrust to this object.
void tree::Physical::applyThrust(bool direction)
{
    m_currentThrustPower = direction ? m_thrustPower : -m_thrustPower;
    m_body->ApplyForceToCenter(
        tree::Math::createVector(
            this->getAngle(),
            m_currentThrustPower
        ),
        true
    );
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

    float distance = Math::distance(this->getPosition(), other->getPosition());

    if (distance == 0) {
        return;
    }

    this->applyForce(
        Math::setMagnitude(
            other->getPosition() - this->getPosition(),

            tree::GRAVITATIONAL_CONSTANT
            * this->getMass()
            * other->getMass()
            / std::pow(distance, 2)
        )
    );
}

// Gets the total force being applied next step.
b2Vec2 tree::Physical::getTotalForce() const
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
b2Vec2 tree::Physical::estimateLinearVelocity() const
{
    return this->getLinearVelocity() + ((1 / 120.0f) * m_totalForce);
}

// Adds the physical transform to a drawing transform.
void tree::Physical::addPhysicalTransform(sf::Transform &transform) const
{
    transform.translate(this->getPixelPosition());
    transform.rotate(tree::Math::degrees(m_body->GetAngle()));
}
