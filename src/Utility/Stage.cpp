#include <tree/Physics/Collisions.hpp>
#include <tree/Utility/Stage.hpp>
#include <tree/Utility/Collection.hpp>

// Destructor.
tree::Stage::~Stage()
{
    this->clear();
}

// Queues an object to be added on the stage.
void tree::Stage::add(tree::Object *object, bool assignStage)
{
    if (assignStage) {
        object->assignStage(this);
    }
    this->newObjects.push_back(object);
}

// Queues an object to be removed from the stage.
void tree::Stage::remove(tree::Object *object)
{
    this->removeObjects.insert(object);
}

// Queues an object to be destroyed from the entire game.
void tree::Stage::destroy(tree::Object *object)
{
    this->destroyObjects.insert(object);
}

// Adds and destroys queued objects.
void tree::Stage::update()
{
    static tree::Physical *physical;

    // Add objects.
    for (auto object : this->newObjects) {

        if (object->isMessage()) {
            this->messages.push_back(
                dynamic_cast<tree::Message*>(object)
            );
        }

        if (object->isActor()) {
            this->actors.push_back(
                dynamic_cast<tree::Actor*>(object)
            );
        }

        if (object->isDrawable() && !object->isMessage()) {
            this->drawables.push_back(
                dynamic_cast<tree::Drawable*>(object)
            );
        }

        if (object->isGui()) {
            this->guis.push_back(
                dynamic_cast<tree::Gui*>(object)
            );
        }

        if (object->isExpirable()) {
            this->expirables.push_back(
                dynamic_cast<tree::Expirable*>(object)
            );
        }

        if (object->isPhysical()) {
            physical = dynamic_cast<tree::Physical*>(object);

            this->physicals.push_back(physical);

            if (physical->createsGravity) {
                this->gravities.push_back(physical);
            }
        }

        if (object->isLifeform()) {
            this->lifeforms.push_back(
                dynamic_cast<tree::Lifeform*>(object)
            );
        }
    }
    this->newObjects.clear();

    // Remove objects.
    for (auto object : this->removeObjects) {

        physical = dynamic_cast<tree::Physical*>(object);

        tree::remove(
            this->messages,
            dynamic_cast<tree::Message*>(object)
        );

        tree::remove(
            this->actors,
            dynamic_cast<tree::Actor*>(object)
        );

        // Drawables. Includes GUIs.
        tree::remove(
            this->drawables,
            dynamic_cast<tree::Drawable*>(object)
        );

        tree::remove(
            this->expirables,
            dynamic_cast<tree::Expirable*>(object)
        );

        tree::remove(
            this->physicals, physical
        );

        tree::remove(
            this->gravities, physical
        );

        tree::remove(
            this->lifeforms,
            dynamic_cast<tree::Lifeform*>(object)
        );
    }
    this->removeObjects.clear();

    // Destroy objects.
    for (auto object : this->destroyObjects) {

        physical = dynamic_cast<tree::Physical*>(object);

        tree::remove(
            this->messages,
            dynamic_cast<tree::Message*>(object)
        );

        tree::remove(
            this->actors,
            dynamic_cast<tree::Actor*>(object)
        );

        // Drawables. Includes GUIs.
        tree::remove(
            this->drawables,
            dynamic_cast<tree::Drawable*>(object)
        );

        tree::remove(
            this->expirables,
            dynamic_cast<tree::Expirable*>(object)
        );

        tree::remove(
            this->physicals, physical
        );

        tree::remove(
            this->gravities, physical
        );

        tree::remove(
            this->lifeforms,
            dynamic_cast<tree::Lifeform*>(object)
        );

        // Destroy object.
        delete object;
    }

    this->destroyObjects.clear();
}

// Immediately destroys all objects from the stage.
void tree::Stage::clear()
{
    // Cleanup physics.
    tree::collisions.clear();

    // Collect objects to destroy.
    for (auto message : this->messages) {
        this->destroy(message);
    }
    for (auto actor : this->actors) {
        this->destroy(actor);
    }

    // Drawables. Includes GUIs.
    for (auto drawable : this->drawables) {
        this->destroy(drawable);
    }
    for (auto expirable : this->expirables) {
        this->destroy(expirable);
    }
    for (auto physical : this->physicals) {
        this->destroy(physical);
    }
    for (auto lifeform : this->lifeforms) {
        this->destroy(lifeform);
    }

    // Destroy objects.
    this->newObjects.clear();
    this->update();
}

// Expires all messages.
void tree::Stage::expireMessages()
{
    for (auto message : this->messages) {
        message->expire();
    }
}
