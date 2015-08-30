#include <tree/Object/Nugget.hpp>

// Adds a nugget to this collection.
void tree::Nuggets::add(tree::nugget newNugget, unsigned int quantity)
{
    unsigned int i = 0;

    // Find nugget.
    while (i < this->list.size()) {
        if (this->list[i].type == newNugget) {
            this->list[i].count += quantity;
            break;
        }

        i++;
    }

    // Add nugget.
    if (i >= this->list.size()) {
        i = this->list.size();

        NuggetComposition comp;
        comp.type = newNugget;
        comp.count = quantity;
        this->list.push_back(comp);
    }

    // Update nugget composition.
    this->list[i].percent = this->list[i].count / this->total();
    std::sort(this->list.begin(), this->list.end());
}

// Gets the total number of nuggets in this collection.
unsigned int tree::Nuggets::total() const
{
    unsigned int result = 0;
    for (auto comp : this->list) {
        result += comp.count;
    }
    return result;
}
