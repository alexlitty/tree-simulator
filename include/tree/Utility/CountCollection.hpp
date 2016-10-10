#ifndef TREESIMULATOR_UTILITY_COUNT_COLLECTION_HPP
#define TREESIMULATOR_UTILITY_COUNT_COLLECTION_HPP

#include <map>

namespace tree
{
    template <typename T>
    class CountCollection
    {
        std::map<T, unsigned int> collection;

    public:
        /**
         * Adds an item to the collection.
         */
        void add(T item, unsigned int amount = 1)
        {
            this->collection[item] += amount;
        }

        /**
         * Adds items from another collection.
         */
        void add(CountCollection<T> &other)
        {
            for (auto &kv : other.collection) {
                this->add(kv.first, kv.second);
            }
        }

        /**
         * Removes an item from the collection.
         */
        void remove(T item, unsigned int amount = 1)
        {
            if (amount > this->collection[item]) {
                this->collection[item] = 0;
            }

            else {
                this->collection[item] -= amount;
            }
        }

        /**
         * Removes items from this collection that are in another.
         */
        void remove(CountCollection<T> &other)
        {
            for (auto &kv : other.collection) {
                this->remove(kv.first, kv.second);
            }
        }

        /**
         * Clears the collection of all items.
         */
        void clear()
        {
            this->collection.clear();
        }

        /**
         * Whether this collection is empty.
         */
        bool isEmpty()
        {
            for (auto &kv : this->collection) {
                if (kv.second) {
                    return false;
                }
            }
            return true;
        }

        /**
         * Whether this collection contains all the items in another.
         */
        bool contains(CountCollection<T> &other)
        {
            for (auto &kv : other.collection) {
                if (this->collection[kv.first] < kv.second) {
                    return false;
                }
            }
            return true;
        }

        /**
         * Returns a total count of all items.
         */
        unsigned int count() const
        {
            unsigned int result = 0;
            for (auto &kv : this->collection) {
                result += kv.second;
            }
            return result;
        }

        /**
         * Accesses item counts.
         */
        unsigned int operator [](T item)
        {
            return this->collection[item];
        }

    };
}

#endif
