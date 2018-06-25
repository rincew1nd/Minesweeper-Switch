#include "DrawableObject.hpp"

DrawableObject::DrawableObject(int x, int y, int w, int h)
{
    _rect = new SDL_Rect();
    _rect->x = x;
    _rect->y = y;
    _rect->w = w;
    _rect->h = h;
    _isVisible = true;
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
    if (_isVisible)
    {
        SDL_SetRenderDrawColor(renderer, _color->r, _color->g, _color->b, _color->a);
        if (_texture != NULL)
            SDL_RenderCopy(renderer, _texture, NULL, _rect);
        else
            SDL_RenderFillRect(renderer, _rect);
    }
}

void DrawableObject::SetTexture(SDL_Texture* texture)
{
    _texture = texture;
}

void DrawableObject::SetVisible(bool visibility)
{
    _isVisible = visibility;
}

bool DrawableObject::IsVisible()
{
    return _isVisible;
}

SDL_Rect* DrawableObject::GetRect() { return _rect; }