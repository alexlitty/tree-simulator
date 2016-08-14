#ifndef TREESIMULATOR_COMPONENT_OBJECT_HPP
#define TREESIMULATOR_COMPONENT_OBJECT_HPP

#include <vector>

namespace tree
{
    /**
     * An object inside the game.
     */
    class Object
    {
    protected:
        bool m_isDrawable = false;
        bool m_isGui = false;
        bool m_isExpirable = false;
        bool m_isIntel = false;
        bool m_isLifeform = false;
        bool m_isMessage = false;
        bool m_isPhysical = false;
        bool m_isNuggetable = false;

    public:

        /**
         * Deconstructor.
         */
        virtual ~Object();

        bool isDrawable() const;
        bool isGui() const;
        bool isExpirable() const;
        bool isIntel() const;
        bool isLifeform() const;
        bool isMessage() const;
        bool isPhysical() const;
        bool isNuggetable() const;
    };

    /**
     * Specialized vector to pass object information.
     */
    typedef std::vector<Object*> Objects;
}

#endif
