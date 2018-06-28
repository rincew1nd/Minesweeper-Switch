#include "TouchableObject.hpp"

TouchableObject::TouchableObject(int x, int y, int w, int h)
    : GraphicalObject(x, y, w, h) {}

void TouchableObject::SetAction(std::function<void()> func)
{
    _onPress = func;
}

bool TouchableObject::Hovered(touchPosition* pos)
{
    return pos->px >= _rect->x && pos->px <= _rect->x + _rect->w &&
           pos->py >= _rect->y && pos->py <= _rect->y + _rect->h;
}