#ifndef TREESIMULATOR_PHYSICS_BOUNDARY_HPP
#define TREESIMULATOR_PHYSICS_BOUNDARY_HPP

#include <SFML/Graphics.hpp>
#include "../Component/Drawable.hpp"
#include "Bounding/Line.hpp"
#include "Bounding/Box.hpp"

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
         * For box boundaries, this will be a tree::Bounding::Box.
         *
         * For ellipse boundaries, this will be a @@@.
         */
        void *info;

    public:

        // The physical transformation of this boundary.
        const sf::Transform *transform;

        /**
         * Default constructor.
         */
        Boundary();

        /**
         * Constructors for different bounding methods.
         */
        Boundary(tree::Line line);
        Boundary(tree::Bounding::Box& box);

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
        void swap(Boundary& other);

        /**
         * Deletes the information about this boundary.
         *
         * The information pointer is not reset. Reassign it immediately.
         *
         * The boundary type remains unchanged.
         */
        void deleteInfo();

        /**
         * Applies the current transformation to bounding information.
         */
        void update();

        /**
         * Assigns new parameters to this boundary.
         */
        void set(tree::Line line);
        void set(tree::Bounding::Box& box);

        /**
         * Blindly retrieves the parameters for this boundary type.
         */
        tree::Bounding::Box* getBox();

        /**
         * Checks if this boundary contains a point.
         */
        bool contains(sf::Vector2f& point);

        /**
         * Checks if this boundary intersects a line.
         */
        bool collides(sf::Vector2f& start, sf::Vector2f& end, sf::Vector2f &result);

        /**
         * Checks if this boundary collides with another boundary.
         *
         * Result is filled with the nearest intersection point, if any.
         */
        bool collides(Boundary& other, Line& trajectory, sf::Vector2f& result);

        /**
         * Returns the nearest point of two boundaries.
         */
        void nearestPoints(tree::Boundary& other, sf::Vector2f& thisResult, sf::Vector2f& otherResult);

        /**
         * Assignment operator.
         */
        Boundary& operator=(Boundary other);

        /**
         * Draw this boundary.
         *
         * Inefficient. Use for debugging only.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif
