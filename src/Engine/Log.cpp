#include <iostream>
#include <tree/Engine/Log.hpp>

void tree::log(const char* type, const char* msg)
{
    std::cout << "[" << type << "] " << msg << std::endl;
}

void tree::info(const char* msg)
{
    tree::log("INFO", msg);
}
