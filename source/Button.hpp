#pragma once

#include <switch.h>

#include <string>
#include <functional>

#include "Engine/SpriteObject.hpp"
#include "Engine/TouchableObject.hpp"

class Button : public SpriteObject, public TouchableObject
{
    public:
        Button(int, int, int, int, std::string);
        Button(int, int, int, int, std::string, std::function<void()>);
        std::string GetName() { return _name; };
        
    private:
        std::string _name;
};