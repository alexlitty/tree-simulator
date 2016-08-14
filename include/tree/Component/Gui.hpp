#ifndef TREESIMULATOR_COMPONENT_GUI_HPP
#define TREESIMULATOR_COMPONENT_GUI_HPP

namespace tree
{
    /**
     * An object which is part of the GUI.
     */
    class Gui : virtual public Drawable
    {

    public:
        /**
         * Constructor.
         */
        Gui();

        /**
         * Draws the GUI object.
         */
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    };
}

#endif
