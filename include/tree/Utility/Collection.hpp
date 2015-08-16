#ifndef TREESIMULATOR_UTILITY_COLLECTION_HPP
#define TREESIMULATOR_UTILITY_COLLECTION_HPP

#include <vector>

namespace tree
{
    template <typename T>
    void remove(std::vector<T> &vector, T &value)
    {
        vector.erase(
            std::remove(
                vector.begin(),
                vector.end(),
                value
            ),
            vector.end()
        );
    }
}

#endif
