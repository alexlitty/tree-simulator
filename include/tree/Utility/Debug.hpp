#ifndef TREESIMULATOR_UTILITY_DEBUG
#define TREESIMULATOR_UTILITY_DEBUG

#include <iostream>

namespace tree
{
    extern bool debug;

    /**
     * Print a string to the console.
     *
     * Used for quick debugging.
     */
    void pp(std::string string);
}

#endif
