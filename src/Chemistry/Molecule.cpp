#include <tree/Chemistry/MoleculeRecipes.hpp>
#include <tree/Engine/Error.hpp>

// Gets the name of a molecule as a string.
std::string tree::getMoleculeName(tree::Molecule molecule)
{
    switch(molecule) {
        case Molecule::Water:
            return "Water";
        case Molecule::Oxygen:
            return "Oxygen";
        case Molecule::Hydrogen:
            return "Hydrogen";
        default:
            return "???";
    }
}

// Generates the most interesting molecule possible.
tree::Molecule tree::generateMolecule(ElementCollection &elements)
{
    for (auto &kv : tree::MoleculeRecipes) {
        if (elements.contains(kv.second)) {
            elements.remove(kv.second);
            return kv.first;
        }
    }

    throw new Error("No molecule can be generated!");
}
