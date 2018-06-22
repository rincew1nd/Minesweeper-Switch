#include "Button.hpp"

Button::Button(int x, int y, int w, int h)
{
    rect = new SDL_Rect();
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

void Button::SetColor(int r, int g, int b, int a)
{
    color = new SDL_Color();
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
}

void Button::SetColor(int r, int g, int b)
{
    SetColor(r, g, b, 255);
}

void Button::Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_RenderFillRect(renderer, rect);
}