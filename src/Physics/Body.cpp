#include <tree/Engine/Error.hpp>
#include <tree/Physics/Body.hpp>
#include <tree/Physics/World.hpp>

// Constructor.
tree::physics::Body::Body(bool dynamic, tree::Vector position)
{
    b2BodyDef def;
    def.position = position;

    if (dynamic) {
        def.type = b2_dynamicBody;
    } else {
        def.type = b2_staticBody;
    }

    this->body = tree::physics::world.CreateBody(&def);
}

// Destructor.
tree::physics::Body::~Body()
{
    tree::physics::world.DestroyBody(this->body);
}

// Maintenance methods.
void tree::physics::Body::updateMass()
{
    this->body->ResetMassData();
}

// Owner.
void tree::physics::Body::setOwner(void *owner)
{
    this->body->SetUserData(owner);
}

void* tree::physics::Body::getOwner()
{
    void *owner = this->body->GetUserData();

    if (!owner) {
        throw new tree::Error("Physics body is missing an owner!");
    }

    return owner;
}

// Position.
void tree::physics::Body::setPosition(tree::Vector position)
{
    this->body->SetTransform(position, this->getAngle().radians());
}

tree::Vector tree::physics::Body::getPosition() const
{
    return this->body->GetWorldCenter();
}

tree::Vector tree::physics::Body::getPixelPosition() const
{
    return this->getPosition() * tree::PIXELS_PER_METER;
}

// Angle.
void tree::physics::Body::setAngle(tree::Angle angle)
{
    bool originalFixedRotation = this->getFixedRotation();

    this->setFixedRotation(false);
    this->body->SetTransform(this->getPosition(), angle.radians());
    this->setFixedRotation(originalFixedRotation);
}

tree::Angle tree::physics::Body::getAngle() const
{
    return tree::Angle::fromRadians(this->body->GetAngle());
}

// Fixed rotation.
void tree::physics::Body::setFixedRotation(bool fixedRotation)
{
    this->body->SetFixedRotation(fixedRotation);
}

bool tree::physics::Body::getFixedRotation() const
{
    return this->body->IsFixedRotation();
}

// Miscellaneous setters.
void tree::physics::Body::setType(b2BodyType type)
{
    this->body->SetType(type);
}

void tree::physics::Body::setAngularDamping(float angularDamping)
{
    this->body->SetAngularDamping(angularDamping);
}

// Miscellaneous getters.
float tree::physics::Body::getMass() const
{
    return this->body->GetMass();
}

b2Body* tree::physics::Body::getInternalBody()
{
    return this->body;
}
