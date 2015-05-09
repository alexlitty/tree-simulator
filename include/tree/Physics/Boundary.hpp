#ifndef TREESIMULATOR_PHYSICS_BOUNDARY_BOX_HPP
#define TREESIMULATOR_PHYSICS_BOUNDARY_BOX_HPP

#include <SFML/Graphics.hpp>
#include "../Component/Drawable.hpp"
#include "../Math/Line.hpp"

namespace tree
{
    /**
     * Boundary implementations.
     */
    class Boundary : public tree::Drawable
    {
    public:
        
        // Representation of boundary types.
        enum class TYPE
        {
            LINE,
            BOX,
            ELLIPSE,
        };

    protected:

        // Type of boundary.
        TYPE type;

        /**
         * Information about this boundary.
         *
         * For line boundaries, this will be a tree::Line.
         *
         * For box boundaries, this will be a sf::FloatRect.
         *
         * For ellipse boundaries, this will be a @@@.
         */
        void *info;

    public:

        /**
         * Constructors for different boundaries.
         */
        Boundary();
        Boundary(tree::Line line);
        Boundary(sf::FloatRect box);

        /**
         * Copy constructor.
         */
        Boundary(Boundary& other);

        /**
         * Move constructor.
         */
        Boundary(Boundary&& other);

        /**
         * Destructor.
         */
        ~Boundary();

        /**
         * Swaps this boundary with another boundary.
         */
        void Swap(Boundary& other);

        /**
         * Deletes the information about this boundary.
         *
         * The information pointer is not reset. Reassign it immediately.
         *
         * The boundary type remains unchanged.
         */
        void DeleteInfo();

        /**
         * Assigns new parameters to this boundary.
         */
        void Set(tree::Line line);
        void Set(sf::FloatRect box);

        /**
         * Checks if this boundary collides with another boundary.
         *
         * Result is filled with the nearest intersection point, if any.
         */
        bool Collides(Boundary& other, sf::Vector2f& result);

        /**
         * Assignment operator.
         */
        Boundary& operator=(Boundary other);

        /**
         * Draw this boundary.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif
