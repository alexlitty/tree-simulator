#include <tree/Object/PlanetBranches.hpp>

tree::PlanetBranches::PlanetBranches(Vector _origin, Vector _goal)
: origin(_origin),
  goal(_goal)
{
    // Create path for branch to follow.
    path.setPrimitiveType(sf::LinesStrip);
    Vector current = _origin;
    while (current != goal) {

        // Determine x coordinate.
        if (tree::similar(current.x, goal.x, 1.0f)) {
            current.x = goal.x;
        }
        else if (current.x < goal.x) {
            current.x += 0.5f;
        }
        else {
            current.x -= 0.5f;
        }

        // Determine y coordinate.
        if (tree::similar(current.y, goal.y, 1.0f)) {
            current.y = goal.y;
        }
        else if (current.y < goal.y) {
            current.y += 0.5f;
        }
        else {
            current.y -= 0.5f;
        }

        // Add coordinate.
        sf::Vertex vertex;
        vertex.position = sf::Vector2f(current.x, current.y);
        vertex.color = sf::Color::Magenta;
        path.append(vertex);
    }
}

void tree::PlanetBranches::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->path, states);
}
