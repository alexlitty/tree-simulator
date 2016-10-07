#ifndef TREESIMULATOR_CHEMISTRY_MOLECULE
#define TREESIMULATOR_CHEMISTRY_MOLECULE

#include <string>
#include <vector>

#include <tree/Chemistry/Element.hpp>

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

    // A named group of elements.
    class Molecule
    {
        std::string name;

        tree::ElementCollection elements;

    public:
        /**
         * Constructor.
         *
         * Takes a collection of elements and generates the most interesting
         * molecule possible, removing the required elements out of the
         * collection.
         */
        Molecule(ElementCollection &inventory);
    };
}

#endif
