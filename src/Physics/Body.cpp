#include <tree/Physics/Body.hpp>
#include <tree/Physics/World.hpp>

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

tree::physics::Body::~Body()
{
    tree::physics::world.DestroyBody(this->body);
}

void tree::physics::Body::setOwner(void *owner)
{
    this->body->SetUserData(owner);
}

void tree::physics::Body::setType(b2BodyType type)
{
    this->body->SetType(type);
}

void tree::physics::Body::setAngularDamping(float angularDamping)
{
    this->body->SetAngularDamping(angularDamping);
}

void tree::physics::Body::setFixedRotation(bool fixedRotation)
{
    this->body->SetFixedRotation(fixedRotation);
}
