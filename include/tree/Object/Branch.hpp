#ifndef TREESIMULATOR_OBJECT_BRANCH_HPP
#define TREESIMULATOR_OBJECT_BRANCH_HPP

#include <tree/Component/Actor.hpp>
#include <tree/Component/Drawable.hpp>
#include <tree/Component/Physical.hpp>

namespace tree
{
    /**
     * Base object for all tree branches.
     */
    class Branch : virtual public Actor, virtual public Drawable
    {
    protected:

        // Physical parent of this branch.
        Physical *m_parent = nullptr;

        // Whether the special abilities of this branch are activated.
        bool m_activated = false;

        // Whether this branch has been permanently placed.
        bool m_placed = false;

    public:

        std::vector<b2Fixture*> fixtures;

        /**
         * Activate the special abilities of this branch.
         */
        void activate(bool activated = true);

        /**
         * Show the preview of this branch.
         */
        void preview(Physical *parent, b2Vec2 anchor, b2Vec2 position);

        /**
         * Handle the branch previewing.
         */
        virtual void onPreview(b2Vec2 anchor, b2Vec2 position) = 0;

        /**
         * Hide the preview of this branch.
         */
        void hidePreview();

        /**
         * Whether this branch is being previewed.
         */
        bool isPreviewing() const;

        /**
         * Place this branch permanently.
         */
        virtual void place() = 0;

        /**
         * Whether this branch has been permanently placed.
         */
        bool isPlaced() const;
    };
}

#endif
