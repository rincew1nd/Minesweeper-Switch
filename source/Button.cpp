#include "Button.hpp"

Button::Button(int x, int y, int w, int h, std::string name, std::function<void()> func)
    : GraphicalObject(x, y, w, h)
{
    _name = name;
    SetAction(func);
}

Button::Button(int x, int y, int w, int h, std::string name)
    : GraphicalObject(x, y, w, h)
{
    _name = name;
}