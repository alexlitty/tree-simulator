#ifndef TREESIMULATOR_OBJECT_INTERNAL_PLAYEREDITOR_HPP
#define TREESIMULATOR_OBJECT_INTERNAL_PLAYEREDITOR_HPP

#include <tree/Component.hpp>
#include <tree/Layer/Type.hpp>
#include <tree/Object/Player.hpp>

namespace tree
{
    class PlayerEditor : public Actor, public Drawable
    {
        tree::Player *player;
        tree::Branch *currentBranch;
        tree::Branch *previewBranch;
        bool previewActive;

    public:

        /**
         * Constructor.
         */
        PlayerEditor(tree::Player *player);

        /**
         * Destructor.
         */
        ~PlayerEditor();

        /**
         * Selects the next or parent branch.
         */
        void selectNextBranch(tree::BranchDirection direction);
        void selectParentBranch();

        /**
         * Perform editing.
         */
        bool act(tree::Stage &stage) override;

        /**
         * Draw editor elements.
         */
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}

#endif
