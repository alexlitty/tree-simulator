#include <tree/Engine/Constant.hpp>

const char* const tree::version = "Alpha";

const float tree::GRAVITATIONAL_CONSTANT = 6.67E-9; // -11

const uint16_t tree::COLLISION_WORLD = 0x0001;
const uint16_t tree::COLLISION_FRIEND = 0x0002;
const uint16_t tree::COLLISION_ENEMY = 0x0004;
const uint16_t tree::COLLISION_PARTICLES = 0x0008;
