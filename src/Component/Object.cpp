#include <tree/Component/Object.hpp>

tree::Object::~Object()
{

}

bool tree::Object::isActor() const
{
    return m_isActor;
}

bool tree::Object::isDrawable() const
{
    return m_isDrawable;
}

bool tree::Object::isExpirable() const
{
    return m_isExpirable;
}

bool tree::Object::isIntel() const
{
    return m_isIntel;
}

bool tree::Object::isLifeform() const
{
    return m_isLifeform;
}

bool tree::Object::isPhysical() const
{
    return m_isPhysical;
}
