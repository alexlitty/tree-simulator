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
void tree::Physical::addFixture(b2FixtureDef &fixtureDef)
{
    m_body->CreateFixture(&fixtureDef);
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
void tree::Physical::setPosition(b2Vec2 &pos)
{
    m_body->SetTransform(pos, this->getAngle());
}

// Gets current angle.
float tree::Physical::getAngle() const
{
    return m_body->GetAngle();
}

// Sets current angle.
void tree::Physical::setAngle(float angle)
{
    m_body->SetTransform(this->getPosition(), angle);
}

// Performs a static rotation.
void tree::Physical::addAngle(float angle)
{
    this->setAngle(
        this->getAngle() + angle
    );
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
void tree::Physical::setLinearVelocity(b2Vec2 &velocity)
{
    m_body->SetLinearVelocity(velocity);
}

// Applies force to this object.
void tree::Physical::applyForce(const b2Vec2 &force)
{
    m_body->ApplyForceToCenter(force, true);
}

// Applies gravity from a gravity source.
void tree::Physical::applyGravity(Physical &other)
{
    if (!other.createsGravity || !this->feelsGravity) {
        return;
    }

    float distance = Math::distance(this->getPosition(), other.getPosition());

    if (distance == 0) {
        return;
    }

    this->applyForce(
        Math::setMagnitude(
            other.getPosition() - this->getPosition(),

            tree::GRAVITATIONAL_CONSTANT
            * this->getMass()
            * other.getMass()
            / std::pow(distance, 2)
        )
    );
}

// Adds the physical transform to a drawing transform.
void tree::Physical::addPhysicalTransform(sf::Transform &transform) const
{
    transform.translate(this->getPixelPosition());
    transform.rotate(tree::Math::degrees(m_body->GetAngle()));
}
