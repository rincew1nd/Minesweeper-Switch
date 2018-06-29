#pragma once

#include <string>

#include "SpriteObject.hpp"

class Button : public SpriteObject
{
    public:
        Button(int, int, int, int, std::string);
        Button(int, int, int, int, std::string, std::function<void()>);
        std::string GetName() { return _name; };
        
    private:
        std::string _name;
};