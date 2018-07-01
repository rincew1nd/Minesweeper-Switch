#include "Button.hpp"

Button::Button(int x, int y, int w, int h, std::string name, std::function<void()> func) : SpriteObject(x, y, w, h)
{
    _name = name;
    SetAction(func);
}

Button::Button(int x, int y, int w, int h, std::string name) : SpriteObject(x, y, w, h)
{
    _name = name;
}