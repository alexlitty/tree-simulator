#ifndef TREESIMULATOR_OBJECT_BULLET_HPP
#define TREESIMULATOR_OBJECT_BULLET_HPP

#include <tree/Component/Drawable.hpp>
#include <tree/Component/Physical.hpp>

namespace tree
{
    /**
     * Base class for all bullets.
     */
    class Bullet : public Drawable, public Physical
    {

    public:

    };
}

#endif
