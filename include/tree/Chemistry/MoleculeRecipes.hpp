#ifndef TREESIMULATOR_CHEMISTRY_MOLECULE_RECIPES_HPP
#define TREESIMULATOR_CHEMISTRY_MOLECULE_RECIPES_HPP

#include <string>
#include <vector>

#include <tree/Chemistry/Molecule.hpp>

namespace tree
{
    /**
     * Retrieves all the elements composing a molecule collection.
     */
    ElementCollection getElements(MoleculeCollection& molecules);

    /**
     * Generates the most interesting molecules from an element collection.
     */
    MoleculeCollection generateMolecules(ElementCollection elements);

    extern std::map<Molecule, ElementCollection> MoleculeRecipes;
}

#endif
