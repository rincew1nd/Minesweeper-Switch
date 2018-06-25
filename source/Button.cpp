#include "Button.hpp"

Button::Button(int x, int y, int w, int h, std::string name)
    : DrawableObject(x, y, w, h)
{
    Name = name;
}