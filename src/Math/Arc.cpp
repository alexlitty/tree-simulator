#include <tree/Math/Arc.hpp>

void tree::makeArc(sf::VertexArray &vertices, tree::Vector start, tree::Vector end, float magnitude)
{
    sf::Vertex vertex;

    Vector current = start;
    Vector magnified;

    Vector center = start.center(end);
    unsigned int steps = 10;
    Vector increment(
        (end.x - start.x) / steps,
        (end.y - start.y) / steps
    );

    Angle angle = start.getAngle(center);
    angle.addDegrees(90.0f);

    // Initialize vertices with a center vertex.
    vertices.clear();
    vertices.setPrimitiveType(sf::TrianglesFan);
    vertex = center;
    vertex.color = sf::Color::Magenta;
    vertices.append(vertex);

    // Incrementally add remaining vertices.
    vertex = current;
    vertex.color = sf::Color::Cyan;
    vertices.append(vertex);
    while (current != end) {
        current += increment;
        if ((increment.x > 0.0f && current.x > end.x) || (increment.x < 0.0f && current.x < end.x)) {
            current.x = end.x;
        }
        if ((increment.y > 0.0f && current.y > end.y) || (increment.y < 0.0f && current.y < end.y)) {
            current.y = end.y;
        }
        
        magnified = current;
        magnified.extend(angle, magnitude);

        vertex = magnified;
        vertex.color = sf::Color::Red;
        vertices.append(vertex);
    }
    vertex = end;
    vertex.color = sf::Color::Cyan;
    vertices.append(vertex);
}
