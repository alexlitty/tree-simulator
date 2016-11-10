#include <tree/Component/Drawable.hpp>
#include <tree/Engine/Error.hpp>

// Constructor.
tree::Drawable::Drawable()
{
    m_isDrawable = true;
}

// Replace ambiguous retrieval of rotation.
float tree::Drawable::getRotation() const
{
    throw new Error("ambiguous getRotation");
}

tree::Angle tree::Drawable::getAngle() const
{
    tree::Angle angle;
    angle.degrees(sf::Transformable::getRotation());
    return angle;
}

// Replace ambiguous setting of rotation.
void tree::Drawable::setRotation(float angle)
{
    throw new Error("ambiguous setRotation");
}

void tree::Drawable::setAngle(tree::Angle angle)
{
    sf::Transformable::setRotation(angle.degrees());
}

// Replace ambiguous rotation.
void tree::Drawable::rotate(float angle)
{
    throw new Error("ambiguous rotate");
}

void tree::Drawable::rotate(tree::Angle &angle)
{
    this->setAngle(this->getAngle() + angle);
}

// Draw.
void tree::Drawable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}
