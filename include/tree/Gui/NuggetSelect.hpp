#ifndef TREESIMULATOR_GUI_NUGGETSELECT_HPP
#define TREESIMULATOR_GUI_NUGGETSELECT_HPP

#include <tree/Component.hpp>

namespace tree
{
    namespace gui
    {
        class NuggetSelect : virtual public Gui
        {
            sf::CircleShape m_preview;

        public:
            /**
             * Constructor.
             */
            NuggetSelect();

            /**
             * Provides the next available nugget.
             */
            void nextNugget(tree::nugget &nugget, bool direction);

            /**
             * Act.
             */
            bool act(tree::Stage &stage) override;

            /**
             * Draw.
             */
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        };
    }
}

#endif
