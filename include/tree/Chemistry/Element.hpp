#ifndef TREESIMULATOR_CHEMISTRY_ELEMENT
#define TREESIMULATOR_CHEMISTRY_ELEMENT

#include <map>

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

    /**
     * Collection of separated elements.
     *
     * Does not represent molecules.
     */
    class ElementCollection
    {
        std::map<Element, unsigned int> elements;

    public:
        /**
         * Adds an element to the collection.
         */
        void add(Element element, unsigned int amount = 1);

        /**
         * Removes an element from the collection.
         */
        void remove(Element element, unsigned int amount = 1);

        /**
         * Clears the collection of all elements.
         */
        void clear();

        /**
         * Accesses element counts.
         */
        unsigned int operator [](Element element);

    };
}

#endif
