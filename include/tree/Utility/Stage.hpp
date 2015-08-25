#ifndef TREESIMULATOR_UTILITY_STAGE_HPP
#define TREESIMULATOR_UTILITY_STAGE_HPP

#include <set>
#include <vector>

namespace tree
{
    class Message;

    /**
     * A stage, on which objects are placed and tracked.
     */
    class Stage
    {
    public:

        /**
         * Window size.
         */
        sf::Vector2f windowSize;

        /**
         * Newly created objects and objects to be destroyed.
         */
        std::vector<tree::Object*> newObjects;
        std::set<tree::Object*> destroyObjects;

        /**
         * Containers of established objects.
         *
         * An object is often inside multiple containers.
         */
        std::vector<tree::Actor*> actors;
        std::vector<tree::Drawable*> drawables;
        std::vector<tree::Expirable*> expirables;
        std::vector<tree::Physical*> physicals;
        std::vector<tree::Physical*> gravities;
        std::vector<tree::Lifeform*> lifeforms;
        std::vector<tree::Message*> messages;

        /**
         * Destructor.
         *
         * Destroys all objects on the stage.
         */
        ~Stage();

        /**
         * Queues an object to be added on the stage.
         */
        void add(tree::Object *object);

        /**
         * Queues an object to be destroyed from the stage.
         */
        void destroy(tree::Object *object);

        /**
         * Adds and destroys queued objects.
         */
        void update();

        /**
         * Immediately destroys all objects from the stage.
         */
        void clear();
    };
}

#include <tree/Gui/Message.hpp>

#endif
