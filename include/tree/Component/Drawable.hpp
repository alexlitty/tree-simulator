#ifndef TREESIMULATOR_COMPONENT_DRAWABLE_HPP
#define TREESIMULATOR_COMPONENT_DRAWABLE_HPP

#include <SFML/Graphics.hpp>
#include <tree/Component/Object.hpp>
#include <tree/Math/Angle.hpp>

namespace tree
{
    class Drawable
    : virtual public Object,
      virtual public sf::Drawable,
      virtual public sf::Transformable
    {
    private:

    protected:
        unsigned char m_alpha;

    public:
        /**
         * Constructor.
         */
        Drawable();

        /**
         * Replace ambiguous sf::Transformable functions.
         */
        float getRotation() const;
        Angle getAngle() const;

        void setRotation(float angle);
        void setAngle(Angle angle);

        void rotate(float angle);
        void rotate(Angle &angle);

        /**
         * Make the draw method public instead of protected.
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
}

#endif
