#include <tree/Chemistry/MoleculeRecipes.hpp>
#include <tree/Engine/Error.hpp>
#include <tree/Math/Random.hpp>

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

// Generates a random color based on a molecule.
sf::Color tree::getRandomColor(tree::Molecule molecule)
{
    unsigned char hue;

    switch (molecule) {
        case Molecule::Water:
            return sf::Color(
                tree::random(10, 50),
                tree::random(0, 150),
                tree::random(150, 225)
            );
            break;

        case Molecule::Oxygen:
            hue = tree::random(200, 245);
            return sf::Color(hue, hue, hue);
            break;

        case Molecule::Hydrogen:
            return sf::Color(
                tree::random(150, 255),
                tree::random(150, 175),
                0
            );
            break;

        default:
            return sf::Color::White;
    }
}
