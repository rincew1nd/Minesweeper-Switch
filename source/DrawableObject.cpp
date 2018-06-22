#include "DrawableObject.hpp"

DrawableObject::DrawableObject(int x, int y, int w, int h)
{
    _rect = new SDL_Rect();
    _rect->x = x;
    _rect->y = y;
    _rect->w = w;
    _rect->h = h;
}

void DrawableObject::SetColor(int r, int g, int b, int a)
{
    _color = new SDL_Color();
    _color->r = r;
    _color->g = g;
    _color->b = b;
    _color->a = a;
}

void DrawableObject::SetColor(int r, int g, int b)
{
    SetColor(r, g, b, 255);
}

void DrawableObject::Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, _color->r, _color->g, _color->b, _color->a);
    SDL_RenderFillRect(renderer, _rect);
}

int DrawableObject::GetX () { return _rect->x; }
int DrawableObject::GetY () { return _rect->y; }