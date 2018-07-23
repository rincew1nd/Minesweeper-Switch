#include "Widget.hpp"

Widget::Widget(int x, int y, int w, int h)
{
    _widgetPosition = new SDL_Rect();
    _widgetPosition->x = x;
    _widgetPosition->y = y;
    _widgetPosition->w = w;
    _widgetPosition->h = h;

    IsVisible = false;
}

void Widget::SetColor(int r, int g, int b)
{
    SetColor(r, g, b, 255);
}

void Widget::SetColor(int r, int g, int b, int a)
{
    _widgetBackgroundColor = new SDL_Color();
    _widgetBackgroundColor->r = r;
    _widgetBackgroundColor->g = g;
    _widgetBackgroundColor->b = b;
    _widgetBackgroundColor->a = a;
}

void Widget::SetTexture(SDL_Texture* texture)
{
    _widgetBackgroundTexture = texture;
}

void Widget::SetFont(TTF_Font* font)
{
    _font = font;
}

void Widget::Draw(SDL_Renderer* renderer)
{
    if (IsVisible)
    {
        if (_widgetBackgroundTexture != nullptr)
            SDL_RenderCopy(renderer, _widgetBackgroundTexture, NULL, _widgetPosition);
        else
        {
            SDL_SetRenderDrawColor(renderer, 
                _widgetBackgroundColor->r, _widgetBackgroundColor->g, _widgetBackgroundColor->b, _widgetBackgroundColor->a
            );
            SDL_RenderFillRect(renderer, _widgetPosition);
        }
        for(int i = 0; i < _buttons.size(); i++)
            _buttons[i]->Draw(renderer);
        for(int i = 0; i < _textes.size(); i++)
            _textes[i]->Draw(renderer);
    }
}

void Widget::HandleTouch(TouchInfo* ti)
{
    for(int i = 0; i < _buttons.size(); i++)
        if (_buttons[i]->Hovered(ti) && _buttons[i]->IsVisible())
            _buttons[i]->Press();
}