#ifndef TREESIMULATOR_OBJECT_NUGGET_HPP
#define TREESIMULATOR_OBJECT_NUGGET_HPP

#include <algorithm>
#include <vector>

namespace tree
{
    /**
     * Types of nuggets.
     */
    enum class nugget
    {
        invalid,
        spore,
        plasma,
        rock,
        water,
        lava,
    };

    /**
     * Explaination of nugget composition.
     */
    struct NuggetComposition
    {
        tree::nugget type;
        unsigned int count;
        float percent;

        friend bool operator<(const NuggetComposition& left, const NuggetComposition &right) {
            return left.count < right.count;
        }
    };

    /**
     * Collection of nuggets.
     */
    class Nuggets
    {
    public:

        // List of nuggets.
        std::vector<NuggetComposition> list;

        /**
         * Adds a nugget to this collection.
         */
        void add(tree::nugget newNugget, unsigned int quantity = 1);

        /**
         * Gets the total number of nuggets in this collection.
         */
        unsigned int total() const;
    };
}

#endif
