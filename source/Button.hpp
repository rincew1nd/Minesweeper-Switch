#pragma once

#include <switch.h>
#include <string>
#include "DrawableObject.hpp"

class Button : public DrawableObject
{
    public:
        Button(int, int, int, int, std::string);
        std::string Name;
};