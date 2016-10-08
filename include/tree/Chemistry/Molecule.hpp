#ifndef TREESIMULATOR_CHEMISTRY_MOLECULE_HPP
#define TREESIMULATOR_CHEMISTRY_MOLECULE_HPP

#include <string>
#include <vector>

#include <tree/Chemistry/Element.hpp>

namespace tree
{
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
         * given collection.
         */
        Molecule(ElementCollection &inventory);

        /**
         * Convert to string.
         */
        operator std::string() const;
    };

    typedef CountCollection<std::string> MoleculeCollection;
}


#endif
