#ifndef TREESIMULATOR_OBJECT_BULLET_HPP
#define TREESIMULATOR_OBJECT_BULLET_HPP

#include <tree/Component/Drawable.hpp>
#include <tree/Component/Physical.hpp>

namespace tree
{
    /**
     * Base class for all bullets.
     */
    class Bullet : virtual public Drawable, virtual public Physical
    {

    public:

    };
}

#endif
