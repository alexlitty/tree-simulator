#include <tree/Chemistry/MoleculeRecipes.hpp>

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
