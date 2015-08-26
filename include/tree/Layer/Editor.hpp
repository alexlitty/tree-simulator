#ifndef TREESIMULATOR_LAYER_PLAYEREDITOR_HPP
#define TREESIMULATOR_LAYER_PLAYEREDITOR_HPP

#include <tree/Component.hpp>
#include <tree/Layer/Type.hpp>

namespace tree
{
    namespace Layer
    {
        class PlayerEditor : public Layer::Type, public Drawable
        {
            sf::RenderWindow &m_window;
            tree::Player *m_player;
            tree::Branch *m_branch;
            unsigned char m_mode;

        public:

            /**
             * Constructor.
             */
            PlayerEditor(sf::RenderWindow &window, tree::Player *player);

            /**
             * Destructor.
             */
            ~PlayerEditor();

            /**
             * Select new branch to add.
             */
            void select(tree::Branch *branch);

            /**
             * Execute the editor.
             */
            bool execute(std::vector<sf::Event> &events) override;

            /**
             * Draw editor elements.
             */
            void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        };
    }
}

#endif
