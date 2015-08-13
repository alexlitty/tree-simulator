#include <tree/Component/Physical.hpp>
#include <tree/Engine/Constant.hpp>
#include <tree/Math/Geometry.hpp>
#include <tree/Math/Trigonometry.hpp>
#include <tree/Math/Vector.hpp>

// Create a body and add it to the physics system.
void tree::Physical::setBody(b2BodyDef &bodyDef)
{
    bodyDef.userData = this;
    
    // Delete old body, set new body.
    if (m_body != nullptr) {
        deleteBody();
    }
    m_body = tree::Physics::world.CreateBody(&bodyDef);
}

// Deletes the current body and removes it from the physics system.
void tree::Physical::deleteBody()
{
    tree::Physics::world.DestroyBody(m_body);
}

// Constructor.
tree::Physical::Physical()
: m_body(nullptr)
{

}

// Destructor.
tree::Physical::~Physical()
{
    deleteBody();
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

// Get current position.
b2Vec2 tree::Physical::getPosition() const
{
    return m_body->GetWorldCenter();
}

// Sets current position.
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
#include <iostream>
void tree::Physical::applyGravity(Physical &other)
{
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
    transform.translate(tree::Math::vector(m_body->GetPosition()));
    transform.rotate(tree::Math::degrees(m_body->GetAngle()));
}
