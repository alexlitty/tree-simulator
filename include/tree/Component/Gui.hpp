#ifndef TREESIMULATOR_COMPONENT_GUI_HPP
#define TREESIMULATOR_COMPONENT_GUI_HPP

namespace tree
{
    /**
     * An object which is part of the GUI.
     */
    class Gui : virtual public Actor, virtual public Drawable
    {

    public:
        /**
         * Constructor.
         */
        Gui();

        /**
         * Act.
         */
        virtual bool act(tree::Stage &stage) = 0;

        /**
         * Draws the GUI object.
         */
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    };
}

#endif
