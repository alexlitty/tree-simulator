#include <tree/Chemistry/Element.hpp>

// Adds an element to the collection.
void tree::ElementCollection::add(tree::Element element, unsigned int amount)
{
    this->elements[element] += amount;
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

// Clears the collection of all elements.
void tree::ElementCollection::clear()
{
    this->elements.clear();
}

// Accesses element counts.
unsigned int tree::ElementCollection::operator [](Element element)
{
    return this->elements[element];
}
