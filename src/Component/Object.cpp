#include <tree/Component/Object.hpp>
#include <tree/Utility/Stage.hpp>

#include <iostream>

// Constructor.
tree::Object::Object()
: stage(nullptr)
{

}

// Destructor.
tree::Object::~Object()
{
    this->disable();
}

// Assigns this object to a stage.
void tree::Object::assignStage(tree::Stage* assignedStage)
{
    this->stage = assignedStage;
}

// Adds this object to the stage.
void tree::Object::enable()
{
    //this->stage->add(this, false);
}

// Removes this object from the stage.
void tree::Object::disable()
{
    if (this->stage) {
        //this->stage->remove(this);
    }
}

bool tree::Object::isMessage() const
{
    return m_isMessage;
}

bool tree::Object::isActor() const
{
    return m_isActor;
}

bool tree::Object::isDrawable() const
{
    return m_isDrawable;
}

bool tree::Object::isGui() const
{
    return m_isGui;
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

bool tree::Object::isNuggetable() const
{
    return m_isNuggetable;
}
