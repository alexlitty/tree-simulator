#include <tree/Chemistry/Element.hpp>

// Adds an element to the collection.
void tree::ElementCollection::add(tree::Element element, unsigned int amount)
{
    this->elements[element] += amount;
}

// Adds elements from another collection.
void tree::ElementCollection::add(tree::ElementCollection &other)
{
    for (auto &kv : other.elements) {
        this->add(kv.first, kv.second);
    }
}

// Removes an element from the collection.
void tree::ElementCollection::remove(tree::Element element, unsigned int amount)
{
    if (amount > this->elements[element]) {
        this->elements[element] = 0;
    }

    else {
        this->elements[element] -= amount;
    }
}

// Removes elements from this collection that are in another.
void tree::ElementCollection::remove(tree::ElementCollection &other)
{
    for (auto &kv : other.elements) {
        this->remove(kv.first, kv.second);
    }
}

// Clears the collection of all elements.
void tree::ElementCollection::clear()
{
    this->elements.clear();
}

// Whether this collection contains all the elements in another.
bool tree::ElementCollection::contains(tree::ElementCollection &other)
{
    for (auto &kv : this->elements) {
        if (kv.second < other[kv.first]) {
            return false;
        }
    }
    return true;
}

// Accesses element counts.
unsigned int tree::ElementCollection::operator [](Element element)
{
    return this->elements[element];
}
