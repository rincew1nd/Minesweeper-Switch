#include "GameObject.hpp"

GameObject::GameObject(int x, int y, int w, int h)
{
    _rect = new SDL_Rect();
    _rect->x = x;
    _rect->y = y;
    _rect->w = w;
    _rect->h = h;
}

void GameObject::Move(int dx, int dy)
{
    _rect->x += dx;
    _rect->y += dy;
};

void GameObject::SetAction(std::function<void()> func)
{
    _onPress = func;
}

bool GameObject::Hovered(TouchInfo* ti)
{
    return ti->ValueOne >= _rect->x && ti->ValueOne <= _rect->x + _rect->w &&
           ti->ValueTwo >= _rect->y && ti->ValueTwo <= _rect->y + _rect->h;
}