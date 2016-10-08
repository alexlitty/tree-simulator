#ifndef TREESIMULATOR_CHEMISTRY_ELEMENT
#define TREESIMULATOR_CHEMISTRY_ELEMENT

#include <map>
#include <tree/Utility/CountCollection.hpp>

namespace tree
{
    /**
     * Types of elements.
     */
    enum class Element
    {
        Hydrogen,
        Lithium,
        Carbon,
        Oxygen
    };

    typedef CountCollection<Element> ElementCollection;
}


#endif
