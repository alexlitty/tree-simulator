#ifndef TREESIMULATOR_OBJECT_INTERNAL_PLAYEREDITOR_HPP
#define TREESIMULATOR_OBJECT_INTERNAL_PLAYEREDITOR_HPP

#include <tree/Component.hpp>
#include <tree/Layer/Type.hpp>
#include <tree/Object/Player.hpp>

namespace tree
{
    class PlayerEditor : public Actor, public Drawable
    {
        tree::Player *m_player;
        tree::Branch *m_branch;
        unsigned char m_mode;

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
         * Select new branch to add.
         */
        void select(tree::Branch *branch);

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
