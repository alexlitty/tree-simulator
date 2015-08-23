#include <tree/Math/Constant.hpp>
#include <tree/Math/Trigonometry.hpp>
#include <tree/Math/Vector.hpp>

float tree::Math::radians(float degrees)
{
    return tree::angle((degrees * tree::Math::PI) / 180.0f);
}

float tree::Math::degrees(float radians)
{
    return tree::angle(
        (radians * 180.0f) / tree::Math::PI,
        false
    );
}
