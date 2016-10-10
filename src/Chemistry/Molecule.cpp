#include <tree/Chemistry/MoleculeRecipes.hpp>
#include <tree/Engine/Error.hpp>

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
