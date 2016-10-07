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
         * Adds elements from another collection.
         */
        void add(ElementCollection &other);

        /**
         * Removes an element from the collection.
         */
        void remove(Element element, unsigned int amount = 1);

        /**
         * Removes elements from this collection that are in another.
         */
        void remove(ElementCollection &other);

        /**
         * Clears the collection of all elements.
         */
        void clear();

        /**
         * Whether this collection contains all the elements in another.
         */
        bool contains(ElementCollection &other);

        /**
         * Accesses element counts.
         */
        unsigned int operator [](Element element);

    };
}

#endif
