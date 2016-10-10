#include <tree/Chemistry/MoleculeRecipes.hpp>

// Constructor.
tree::Molecule::Molecule(ElementCollection &inventory)
{
    for (auto recipe : tree::MoleculeRecipes) {
        if (inventory.contains(recipe.elements)) {
            inventory.remove(recipe.elements);
            this->elements.add(recipe.elements);
            this->name = recipe.name;
            break;
        }
    }
}

// Convert to string.
tree::Molecule::operator std::string() const
{
    return this->name;
}
