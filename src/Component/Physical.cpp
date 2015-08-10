#include <tree/Component/Physical.hpp>
#include <tree/Math/Trigonometry.hpp>
#include <tree/Math/Vector.hpp>

// Create a body and add it to the physics system.
void tree::Physical::setBody(b2BodyDef &bodyDef)
{
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

// Get current position.
b2Vec2 tree::Physical::getPosition() const
{
    return m_body->GetPosition();
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

// Adds the physical transform to a drawing transform.
void tree::Physical::addPhysicalTransform(sf::Transform &transform) const
{
    transform.translate(tree::Math::vector(m_body->GetPosition()));
    transform.rotate(tree::Math::degrees(m_body->GetAngle()));
}
