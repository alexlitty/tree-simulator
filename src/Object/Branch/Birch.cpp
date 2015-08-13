#include <tree/Math/Vector.hpp>
#include <tree/Object/Branch/Birch.hpp>
#include <tree/Resource/Color.hpp>

// Draw birch leaf.
void tree::branches::BirchLeaf::draw(sf::RenderTarget &target, sf::RenderStates states)
{
    sf::VertexArray temp;
    temp.setPrimitiveType(sf::Points);

    sf::Vertex test(
        tree::Math::vector(this->getPosition()),
        tree::paletteColor(tree::palette::random)
    );

    temp.append(test);

    target.draw(temp, states);
}

// Upkeep leaves.
void tree::branches::Birch::act()
{

}

// Draw branch and leaves.
void tree::branches::Birch::draw(sf::RenderTarget &target, sf::RenderStates states)
{
    for (auto &leaf : m_leaves) {
        leaf.draw(target, states);
    }
}
