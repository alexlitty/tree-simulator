#include <tree/Chemistry/Molecule.hpp>

// Recipe constructor.
tree::MoleculeRecipe::MoleculeRecipe(std::string _name, std::vector<tree::Element> _elements)
: name(_name)
{
    for (auto element : _elements) {
        this->elements.add(element);
    }
}

// Global list of molecule recipes.
std::vector<tree::MoleculeRecipe> tree::MoleculeRecipes = {
    MoleculeRecipe(
        "water",
        {
            tree::Element::Hydrogen,
            tree::Element::Hydrogen,
            tree::Element::Oxygen
        }
    ),

    MoleculeRecipe(
        "hydrogen",
        { tree::Element::Hydrogen }
    ),

    MoleculeRecipe(
        "oxygen",
        { tree::Element::Oxygen }
    )
};

// Molecule constructor.
tree::Molecule::Molecule(ElementCollection &inventory)
{
    for (auto recipe : tree::MoleculeRecipes) {
        if (inventory.contains(recipe.elements)) {
            inventory.remove(recipe.elements);
            this->elements.add(recipe.elements);
            break;
        }
    }
}
