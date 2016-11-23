#ifndef TREESIMULATOR_CHEMISTRY_MOLECULE_HPP
#define TREESIMULATOR_CHEMISTRY_MOLECULE_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <tree/Chemistry/Element.hpp>

namespace tree
{
    enum class Molecule
    {
        Water,
        Oxygen,
        Hydrogen
    };
    typedef CountCollection<Molecule> MoleculeCollection;

    /**
     * Gets the name of a molecule as a string.
     */
    std::string getMoleculeName(Molecule molecule);

    /**
     * Generates the most interesting molecule possible, removing the required
     * elements out of the given collection.
     */
    Molecule generateMolecule(ElementCollection &elements);

    /**
     * Generates a random color based on a molecule.
     */
    sf::Color getRandomColor(Molecule molecule);
}


#endif
