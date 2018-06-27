#include "GraphicalObject.hpp"

GraphicalObject::GraphicalObject(int x, int y, int w, int h)
{
    _rect = new SDL_Rect();
    _rect->x = x;
    _rect->y = y;
    _rect->w = w;
    _rect->h = h;
    _isVisible = true;
}

void GraphicalObject::SetColor(int r, int g, int b, int a)
{
    _color = new SDL_Color();
    _color->r = r;
    _color->g = g;
    _color->b = b;
    _color->a = a;
}

void GraphicalObject::SetColor(int r, int g, int b)
{
    SetColor(r, g, b, 255);
}

void GraphicalObject::Draw(SDL_Renderer *renderer)
{
    if (_isVisible)
    {
        SDL_SetRenderDrawColor(renderer, _color->r, _color->g, _color->b, _color->a);
        SDL_RenderFillRect(renderer, _rect);
    }
}

void GraphicalObject::SetVisible(bool visibility)
{
    _isVisible = visibility;
}

bool GraphicalObject::IsVisible()
{
    return _isVisible;
}

SDL_Rect* GraphicalObject::GetRect() { return _rect; }