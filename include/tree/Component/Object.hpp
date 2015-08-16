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
        bool m_isActor = false;
        bool m_isDrawable = false;
        bool m_isLifeform = false;
        bool m_isPhysical = false;

    public:
        virtual ~Object();

        bool isActor() const;
        bool isDrawable() const;
        bool isLifeform() const;
        bool isPhysical() const;
    };

    /**
     * Specialized vector to pass object information.
     */
    typedef std::vector<Object*> Objects;
}

#endif
