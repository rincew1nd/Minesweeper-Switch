#pragma once
#include <switch.h>
#include <SDL2/SDL.h>

class GraphicalObject
{
    public:
        GraphicalObject(int, int, int, int);
        void SetColor(int, int, int, int);
        void SetColor(int, int, int);
        void Draw(SDL_Renderer*);
        SDL_Rect* GetRect();
        void SetVisible(bool);
        bool IsVisible();

    protected:
        SDL_Rect* _rect;
        SDL_Color* _color;
        bool _isVisible;
};