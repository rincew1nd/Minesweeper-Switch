#pragma once
#include <switch.h>
#include <SDL2/SDL.h>

class DrawableObject
{
    public:
        DrawableObject(int, int, int, int);
        void SetColor(int, int, int, int);
        void SetColor(int, int, int);
        void Draw(SDL_Renderer*);
        int GetX();
        int GetY();
        void SetTexture(SDL_Texture*);
    private:
        SDL_Rect* _rect;
        SDL_Color* _color;
        SDL_Texture* _texture;
};