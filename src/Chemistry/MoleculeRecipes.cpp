#include <tree/Chemistry/MoleculeRecipes.hpp>

// Retrieves all the elements composing a molecule collection.
tree::ElementCollection tree::getElements(tree::MoleculeCollection& molecules)
{
    ElementCollection elements;
    for (auto pair : molecules) {
        for (unsigned int i = 0; i < pair.second; i++) {
            elements.add(MoleculeRecipes[pair.first]);
        }
    }
    return elements;
}

// Generates the most interesting molecules from an element collection.
tree::MoleculeCollection tree::generateMolecules(tree::ElementCollection elements)
{
    MoleculeCollection molecules;
    while (!elements.isEmpty()) {
        molecules.add(tree::generateMolecule(elements));
    }
    return molecules;
}

std::map<tree::Molecule, tree::ElementCollection> tree::MoleculeRecipes = {
    {
        Molecule::Water,
        {
            tree::Element::Hydrogen,
            tree::Element::Hydrogen,
            tree::Element::Oxygen
        }
    },

    {
        Molecule::Hydrogen,
        {
            tree::Element::Hydrogen
        }
    },

    {
        Molecule::Oxygen,
        {
            tree::Element::Oxygen
        }
    }
};
