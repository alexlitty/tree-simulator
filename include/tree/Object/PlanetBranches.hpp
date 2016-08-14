#ifndef TREESIMULATOR_OBJECT_PLANETBRANCHES_HPP
#define TREESIMULATOR_OBJECT_PLANETBRANCHES_HPP

#include <tree/Component/Drawable.hpp>
#include <tree/Math.hpp>

namespace tree
{
    class PlanetBranches : public Drawable
    {

        sf::VertexArray path;
        sf::VertexArray branch;
        Vector origin;
        Vector goal;

    public:
    
        /**
         * Constructor.
         */
        PlanetBranches(Vector _origin, Vector _goal);

        /**
         * Draw.
         */
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}

#endif
