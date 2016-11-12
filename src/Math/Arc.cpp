#include <tree/Math/Arc.hpp>

void tree::makeArc(sf::VertexArray &vertices, tree::Vector start, tree::Vector end, float magnitude, DistributionFunction dist)
{
    sf::Vertex vertex;
    Vector current = start;
    Vector magnified;

    Vector center = start.center(end);
    unsigned int steps = static_cast<unsigned int>(std::ceil(start.distance(end))) * 3;
    Vector increment(
        (end.x - start.x) / steps,
        (end.y - start.y) / steps
    );

    Angle angle = start.getAngle(center);
    angle.addDegrees(90.0f);

    // Incrementally add vertices.
    vertices.append(current);
    while (current != end) {
        current += increment;
        if ((increment.x > 0.0f && current.x > end.x) || (increment.x < 0.0f && current.x < end.x)) {
            current.x = end.x;
        }
        if ((increment.y > 0.0f && current.y > end.y) || (increment.y < 0.0f && current.y < end.y)) {
            current.y = end.y;
        }

        magnified = current;
        magnified.extend(angle, dist(current.progress(start, end)) * magnitude);
        vertices.append(magnified);
    }
    vertices.append(end);
}
