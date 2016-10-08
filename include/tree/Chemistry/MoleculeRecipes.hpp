#ifndef TREESIMULATOR_CHEMISTRY_MOLECULE_RECIPES_HPP
#define TREESIMULATOR_CHEMISTRY_MOLECULE_RECIPES_HPP

#include <string>
#include <vector>

#include <tree/Chemistry/Molecule.hpp>

namespace tree
{
    // Information about a particular kind of molecule.
    struct MoleculeRecipe
    {
        MoleculeRecipe(std::string _name, std::vector<Element> _elements);

        ElementCollection elements;
        std::string name;
    };

    // Global list of molecule recipes.
    extern std::vector<MoleculeRecipe> MoleculeRecipes;
}

#endif
